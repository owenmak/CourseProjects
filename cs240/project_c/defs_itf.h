#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "reader.h"
#include "cargs.h"
#define Table void
#define Row void
Table *r_read(FILE *in);
#include "tree.h"
#include "query.h"
#include "table.h"
#include "column.h"
#include "dt.h"
#include "confmatrix.h"
