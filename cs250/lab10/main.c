#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct X{
  char ch1;
    int i;
	  char ch2;
	    int *p;
		  char str[18];
		    float f;
			};

			struct Y{
			  int i;
			    double *p;
				  double d;
				  };

				  struct List {
				    char * str;
					  struct List * next;
					  };

					  main() {
					    struct X x;
						  struct Y y;
						    struct List * head;

							  x.ch1 = 'A';
							    x.i = 9;
								  x.ch2 = '0';
								    x.p = &x.i;
									  strcpy(x.str, "Hello world");
									    x.f = 2.543;

										  y.i = -5;
										    y.d = 4.5643;
											  y.p = &y.d;

											    head = (struct List *) malloc(sizeof(struct List));
												  head->str=strdup("Welcome ");
												    head->next = (struct List *) malloc(sizeof(struct List));
													  head->next->str = strdup("to ");
													    head->next->next = (struct List *) malloc(sizeof(struct List));
														  head->next->next->str = strdup("cs250");
														    head->next->next->next = NULL;

															  hexdump((char *) &x.ch1, ((char *) &x.ch1)+sizeof(struct X)-1);
															    hexdump((char*) &y.i, ((char*) &y.i)+sizeof(struct Y)-1);
																  hexdump((char*) head, ((char*) head->next->next->str)+sizeof(head->next->next->str));
																  }
