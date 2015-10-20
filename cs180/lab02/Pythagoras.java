/**
 * cs180 - Lab 02
 * get c for c^2 = a^2 + b^2
 * @Zilun Mai, <zmai@purdue.edu>
 */
 import java.util.*;
 public class Pythagoras{
 public double getHypotenuse(int a,int b){
 double h = Math.sqrt(a*a+b*b);
 return h;
 }
 public static void main(String[] args){
 double h;
 Scanner scanner = new Scanner(System.in);
 System.out.println("Enter side 'a': ");
 int a = scanner.nextInt();
 System.out.println("Enter side 'b': ");
 int b = scanner.nextInt();
 Pythagoras p = new Pythagoras();
 h = p.getHypotenuse(a,b);
 System.out.println("Hypotenuse " + h);
 }
 }