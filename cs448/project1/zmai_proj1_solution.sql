
rem CS 448 SQLPLUS Project1

rem Zilun Mai 

prompt query 1

SELECT CNAME
FROM CUSTOMERS
WHERE CUSTOMERS.CNO IN
    (SELECT CNO
     FROM
       (SELECT C.CNO,
               SUM(P.PRICE*OD.QTY+OD.SFEE) AS TOTALSUM
        FROM CUSTOMERS C,
             ORDERS O,
             ODETAILS OD,
             PARTS P
        WHERE C.CNO=O.CNO
          AND O.ONO=OD.ONO
          AND OD.PNO=P.PNO
        GROUP BY(C.CNO)
        ORDER BY(TOTALSUM) DESC)
     WHERE rownum = 1);

prompt query 2

SELECT MAX(SHIPPED- RECEIVED) AS MAX_WAIT
FROM ORDERS O;


prompt query 3

WITH ZIP_DIFF AS
  (SELECT W.WNO,
          WNAME,
          W.ZIP-C.ZIP AS ZIP_DIFF
   FROM WORKERS W,
        CUSTOMERS C,
        ORDERS O
   WHERE O.WNO=W.WNO
     AND O.CNO=C.CNO),
      MAX_DIFF AS
  (SELECT WNO,
          WNAME,
          MAX(ZIP_DIFF) AS DIFF
   FROM ZIP_DIFF
   GROUP BY (WNO,
             WNAME)),
      MIN_DIFF AS
  (SELECT WNO,
          WNAME,
          MIN(ZIP_DIFF) AS DIFF
   FROM ZIP_DIFF
   GROUP BY (WNO,
             WNAME))
SELECT MAX_DIFF.WNO,
       MAX_DIFF.WNAME
FROM MAX_DIFF
INNER JOIN MIN_DIFF ON MAX_DIFF.DIFF=MIN_DIFF.DIFF
AND MAX_DIFF.DIFF=0 ;


prompt query 4

WITH OLEVEL_COUNT AS
  (SELECT P.OLEVEL AS OLEVEL,
          COUNT(DISTINCT OD.PNO) AS PNO_COUNT
   FROM PARTS P,
        ODETAILS OD
   WHERE P.PNO=OD.PNO
   GROUP BY P.OLEVEL)
SELECT OC.OLEVEL AS OLEVEL,
       OC.PNO_COUNT,
       AVG(P.QOH),
       MAX(P.QOH),
       MIN(P.QOH)
FROM PARTS P,
     OLEVEL_COUNT OC
WHERE P.OLEVEL=OC.OLEVEL
GROUP BY(OC.OLEVEL,
         OC.PNO_COUNT);


prompt query 5

SELECT TO_CHAR(TO_DATE(LOW_SALE_MONTH, 'MM'), 'MON') AS LOW_MONTH
FROM
  (SELECT EXTRACT(MONTH
                  FROM O.RECEIVED) AS LOW_SALE_MONTH,
          SUM(P.PRICE*OD.QTY+OD.SFEE) AS SALES
   FROM CUSTOMERS C,
        ORDERS O,
        ODETAILS OD,
        PARTS P
   WHERE C.CNO=O.CNO
     AND O.ONO=OD.ONO
     AND OD.PNO=P.PNO
     AND EXTRACT(YEAR
                 FROM O.RECEIVED) = '1995'
   GROUP BY EXTRACT(MONTH
                    FROM O.RECEIVED)
   ORDER BY(SALES) ASC)
WHERE rownum = 1;


prompt query 6

WITH PNO_CNAME AS
  (SELECT P.PNO,
          C.CNAME
   FROM ORDERS O,
        PARTS P,
        ODETAILS OD,
        CUSTOMERS C
   WHERE P.PNO=OD.PNO
     AND OD.ONO=O.ONO
     AND O.CNO=C.CNO),
      PNO_PAIRS AS
  (SELECT PC1.PNO AS PNO1,
          PC2.PNO AS PNO2,
          COUNT(PC1.CNAME) AS PAIRS
   FROM PNO_CNAME PC1
   CROSS JOIN PNO_CNAME PC2
   WHERE PC1.PNO>PC2.PNO
     AND PC1.CNAME=PC2.CNAME
   GROUP BY(PC1.PNO, PC2.PNO)
   ORDER BY(PAIRS) ASC)
SELECT PNO1,
       PNO2
FROM PNO_PAIRS
WHERE PAIRS =
    (SELECT MIN(PAIRS)
     FROM PNO_PAIRS);



prompt query 7

WITH ONO_SFEE AS
  (SELECT OD.PNO AS PNO,
          SFEE
   FROM PARTS P,
        ORDERS O,
        ODETAILS OD
   WHERE P.PNO=OD.PNO
     AND OD.ONO=O.ONO),
     TCOUNT AS
  (SELECT PNO,
          COUNT(SFEE) AS TOTALCOUNT
   FROM ONO_SFEE
   GROUP BY PNO),
     NCOUNT AS
  (SELECT PNO,
          COUNT(SFEE) AS NONZERO
   FROM ONO_SFEE
   WHERE SFEE > 0
   GROUP BY PNO),
     PNO_RAT AS
  (SELECT TCOUNT.PNO,
          COALESCE(NONZERO,0)/TOTALCOUNT AS RATIO
   FROM TCOUNT
   LEFT JOIN NCOUNT ON TCOUNT.PNO=NCOUNT.PNO),
     PNO_MIN AS
  (SELECT P.PNO AS PNO,
          P.QOH AS QOH,
          P.PNAME AS PNAME
   FROM PARTS P,
        PNO_RAT
   WHERE RATIO=
       (SELECT MIN(RATIO)
        FROM PNO_RAT)
     AND P.PNO=PNO_RAT.PNO)
SELECT PM.PNO AS PNO,
       PNAME,
       QOH,
       SUM(OD.SFEE) AS SUM_SFEE
FROM PNO_MIN PM,
     ODETAILS OD
WHERE OD.PNO = PM.PNO
GROUP BY (PM.PNO,
          QOH,
          PNAME);


prompt query 8

WITH PNO_DOWNFALL
     AS (SELECT P.PNO,
                RECEIVED
         FROM   PARTS P,
                CUSTOMERS C,
                ORDERS O,
                ODETAILS OD
         WHERE  P.PNO = OD.PNO
                AND OD.ONO = O.ONO
                AND O.CNO = C.CNO
         ORDER  BY P.PNO DESC,
                   RECEIVED DESC),
     PNO_DOWNFALL1
     AS (SELECT *
         FROM   (SELECT *
                 FROM   PNO_DOWNFALL
                 MINUS
                 (SELECT *
                  FROM   PNO_DOWNFALL
                  WHERE  ROWNUM = 1))
         ORDER  BY PNO DESC),
     PD_ROW
     AS (SELECT PNO,
                RECEIVED,
                Row_number()
                  OVER (
                    ORDER BY PNO DESC) AS R
         FROM   PNO_DOWNFALL),
     PNO_D
     AS (SELECT PD1.PNO,
                Max(PD1.RECEIVED - PD2.RECEIVED) AS DOWNFALL
         FROM   PD_ROW PD1,
                PD_ROW PD2
         WHERE  PD1.R + 1 = PD2.R
                AND PD1.PNO = PD2.PNO
         GROUP  BY( PD1.PNO ))
SELECT PNAME,
       P.QOH,
       DOWNFALL
FROM   PARTS P,
       PNO_D
WHERE  P.PNO = PNO_D.PNO
ORDER  BY DOWNFALL DESC; 


prompt query 9

SELECT DISTINCT PNAME
FROM   PARTS P,
       CUSTOMERS C,
       ORDERS O,
       ODETAILS OD
WHERE  P.PNO = OD.PNO
       AND OD.ONO = O.ONO
       AND O.CNO = C.CNO
       AND C.CNAME IN (SELECT CNAME
                       FROM   (SELECT CNAME,
                                      Count(PNO) AS PNO_COUNT
                               FROM   (SELECT DISTINCT C.CNAME,
                                                       P.PNO
                                       FROM   CUSTOMERS C,
                                              PARTS P,
                                              ORDERS O,
                                              ODETAILS OD
                                       WHERE  P.PNO = OD.PNO
                                              AND OD.ONO = O.ONO
                                              AND O.CNO = C.CNO)
                               GROUP  BY( CNAME ))
                       WHERE  PNO_COUNT >= 4); 


prompt query 10

WITH MON_AVG
     AS (SELECT *
         FROM   (SELECT MONTH_NAME,
                        Avg(TOTALSUM) AS AVG_SALE
                 FROM   (SELECT To_char(To_date(Extract(MONTH FROM
                                O.RECEIVED), 'MM'),
                                'MON') AS
                                        MONTH_NAME,
                                P.PRICE * OD.QTY + OD.SFEE
                                AS
                                        TOTALSUM
                         FROM   CUSTOMERS C,
                                ORDERS O,
                                ODETAILS OD,
                                PARTS P
                         WHERE  C.CNO = O.CNO
                                AND O.ONO = OD.ONO
                                AND OD.PNO = P.PNO)
                 GROUP  BY MONTH_NAME))
SELECT *
FROM   MON_AVG
WHERE  AVG_SALE = (SELECT Min(AVG_SALE)
                   FROM   MON_AVG); 
