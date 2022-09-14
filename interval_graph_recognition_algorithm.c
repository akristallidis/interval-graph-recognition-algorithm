//Krystallidis Anastasios
//Interval Graph

#include<stdio.h>
#include<stdlib.h>

typedef struct list {	//Struct for vertices neighbours 
	int vertex;
	struct list *next;
}LIST;

typedef struct label {	//Struct for vertices labels
	int epigrafi;
	struct label *next;
}LABEL;

void scan_edges();
void print_graph();
void LBFS();
void LBFS_PLUS();
void LBFS_MUL();
void is_umbrella_free();

int vertices,edges,same_edges=0,*s_return,*s_return_plus,*s_return_plus_plus,*s_return_mul,call;

void scan_edges(LIST *table[],int vertices,int edges)  {

	int i,x,y,state,number=0;
	LIST *tmp1,*tmp2,*tmp3,*tmp4,*elegxos;

	for(i=0;i<vertices;i++)  {	//Vertices table initialization
		table[i]=NULL;
	}
	for(i=0;i<edges;i++)  {
		printf("Insert the edge number %d: ", i+1);
		scanf("%d", &x);	//Read the first vertice of edge
		scanf("%d", &y);	//Read the second vertice of edge
		if (x>vertices || x<0)  {
			printf("\nError-Problem at vertex %d.Exit\n\n",x);
			exit(1);
		}
		if (y>vertices || y<0)  {
			printf("\nError-Problem at vertex %d.Exit\n\n",y);
			exit(1);
		}
		state=0;
		if (table[x-1]!=NULL)  {	//Check for double edge entry
			elegxos=table[x-1];
			while(elegxos!=NULL)  {
				if(elegxos->vertex==y)  {
					state=1;
					same_edges+=1;
					printf("The edge %d %d has allready been stored.\n", x, y);
				}
				elegxos=elegxos->next;
			}
		}
		if(x==y)  {	//Check for entry edge between the same vertice
			state=1;
			same_edges+=1;
			printf("\nThere is no possibility of connection beetwin vertex %d and itself.\n",x);
		}
		if (state==0)  {	//If everything is ok then create the connection between two vertices
			number++;
			tmp1=(LIST*)malloc(sizeof(LIST));
			tmp1->vertex=y;
			tmp1->next=NULL;
			if(table[x-1]==NULL)  {	//Create edge x-y
				table[x-1]=tmp1;
			}
			else  {
				tmp2=table[x-1];
				while(tmp2->next!=NULL)  {
					tmp2=tmp2->next;
				}
				tmp2->next=tmp1;
			}
			tmp3=(LIST*)malloc(sizeof(LIST));
			tmp3->vertex=x;
			tmp3->next=NULL;
			if(table[y-1]==NULL)  {	//Create edge y-x
				table[y-1]=tmp3;
			}
			else  {
				tmp4=table[y-1];
				while(tmp4->next!=NULL)  {
					tmp4=tmp4->next;
				}
				tmp4->next=tmp3;
			}
		}
	}
}

void print_graph(LIST *table[])  {

	int i;
	LIST *tmp5;

	for(i=0;i<vertices;i++)  {	//Print graph
		tmp5=table[i];
		if(tmp5!=NULL)  {	//Check for vertice connection with other vertices
			printf("\n%d:\t%d\t",i+1, tmp5->vertex);
			while(tmp5->next!=NULL)  {
				tmp5=tmp5->next;
				printf("%d\t", tmp5->vertex);
			}
		}
		else
			printf("\n%d:\tNo connection for this vertex", i+1);
	}
	edges=edges-same_edges;	//Compute the vertices and edged number except the duplicate entries
	printf("\n\nThe graph has %d vertices and %d edges!\n\n", vertices, edges);
}

void LBFS(LIST *table[],int korifi)  {

	int i,j,l,m,x,sigma[vertices],flag=0,epilogi=korifi,flag_epilogi=0,count=0,flag2,count2,n,table_korifon[vertices];
	LABEL *tmp,*tmp2,*tmp3,*table_label[vertices],*epil_1,*epil_2;
	LIST *tmp1;

	for(i=0;i<vertices;i++)  {	//Initialize sigma = -1
		sigma[i]=-1;
		table_korifon[i]=i+1;
	}
	epilogi--;
	tmp=(LABEL*)malloc(sizeof(LABEL));	//Memory allocation
	tmp->epigrafi=vertices;
	tmp->next=NULL;
	table_label[epilogi]=tmp;
	for(i=0;i<vertices;i++)  {	//Initialize all vertices label to NULL
		if(i!=epilogi)
			table_label[i]=NULL;
	}
	for(i=vertices;i>=1;i--)  {
		for(m=0;m<vertices;m++)  {	//Take the vertice with the max number
			if(table_korifon[m]!=-1)  {
				epil_1=table_label[epilogi];
				epil_2=table_label[m];
				while(epil_1!=NULL && epil_2!=NULL && flag_epilogi==0)  {
					if(epil_1->epigrafi > epil_2->epigrafi)  {
						flag_epilogi=1;
					}
					else if(epil_1->epigrafi < epil_2->epigrafi)  {
						epilogi=m;
						flag_epilogi=1;
					}
					else  {
						epil_1=epil_1->next;
						epil_2=epil_2->next;
					}
				}
				if(flag_epilogi==0 && epil_1==NULL && epil_2!=NULL)  {
					epilogi=m;
				}
				flag_epilogi=0;
			}
		}
		sigma[count]=epilogi+1;
		for(j=0;j<vertices;j++)  {
			if(epilogi+1==table_korifon[j])  {
				table_korifon[j]=-1;
			}
		}
		tmp1=table[epilogi];
		while(tmp1!=NULL)  {
			x=tmp1->vertex;
			flag=0;
			for(j=0;j<vertices;j++)  {
				if(sigma[j]==x)
					flag=1;
			}
			if(flag==0)  {
				tmp2=(LABEL*)malloc(sizeof(LABEL));
				tmp2->epigrafi=i;
				tmp2->next=NULL;
				if(table_label[x-1]==NULL)
					table_label[x-1]=tmp2;
				else  {
					tmp3=table_label[x-1];
					while(tmp3->next!=NULL)
						tmp3=tmp3->next;
					tmp3->next=tmp2;
				}
			}
			tmp1=tmp1->next;
		}
		count++;
		epilogi=1;
		flag2=0;
		while(flag2==0)  {	//Take a random vertice out of sigma
			flag2=1;
			for(j=0;j<count;j++)  {
				if(sigma[j]==epilogi)  {
					flag2=0;
					epilogi++;
				}
			}
		}
		epilogi--;
	}
	printf("\nσ:\t");
	s_return=(int *)malloc(vertices*sizeof(int));
	for(i=0;i<vertices;i++)  {	//Print sigma and back to main
		printf("%d  ",sigma[i]);
		s_return[i]=sigma[i];
	}
	printf("\n\n");
	free(tmp);
	free(tmp1);
	free(tmp2);
	free(tmp3);
}

void LBFS_PLUS(LIST *table[],int *S)  {

	int i,j,l,m,x,sigma_plus[vertices],flag=0,epilogi=S[vertices-1],flag_epilogi=0,count=0,flag2,count2,n,dexiotera,table_korifon[vertices],table_s[vertices];
	LABEL *tmp,*tmp2,*tmp3,*table_label[vertices],*epil_1,*epil_2;
	LIST *tmp1;
	int pinakas[vertices],count_epilogis,count_elegxou,count_pinaka=0;
	LABEL *tmp_epilogis,*tmp_elegxou;

	for(i=0;i<vertices;i++)  {	//Initialize sigma=-1
		sigma_plus[i]=-1;
		table_korifon[i]=i+1;
	}
	for(i=0;i<vertices;i++)  {
		for(j=0;j<vertices;j++)  {
			if(S[j]==i+1)  {
				table_s[i]=j+1;
			}
		}
	}
	epilogi--;
	tmp=(LABEL*)malloc(sizeof(LABEL));	//Initialize random vertices label equal to the vertices number
	tmp->epigrafi=vertices;
	tmp->next=NULL;
	table_label[epilogi]=tmp;
	for(i=0;i<vertices;i++)  {	//Initialize all the others vertices labels equals to NULL
		if(i!=epilogi)
			table_label[i]=NULL;
	}
	for(i=vertices;i>=1;i--)  {	//Like LBFS for selection the lexicographical max
		for(m=0;m<vertices;m++)  {
			if(table_korifon[m]!=-1)  {
				epil_1=table_label[epilogi];
				epil_2=table_label[m];
				while(epil_1!=NULL && epil_2!=NULL && flag_epilogi==0)  {
					if(epil_1->epigrafi > epil_2->epigrafi)  {
						flag_epilogi=1;
					}
					else if(epil_1->epigrafi < epil_2->epigrafi)  {
						epilogi=m;
						flag_epilogi=1;
					}
					else  {
						epil_1=epil_1->next;
						epil_2=epil_2->next;
					}
				}
				if(flag_epilogi==0 && epil_1==NULL && epil_2!=NULL)  {
					epilogi=m;
					flag_epilogi=1;
				}
				else if(flag_epilogi==0 && epil_1!=NULL && epil_2==NULL)  {
					flag_epilogi=1;
				}
				flag_epilogi=0;
			}
		}
		for(j=0;j<vertices;j++)  {	//Initialize table that contains all the neighbour equals
			pinakas[j]=0;
		}
		pinakas[count_pinaka]=epilogi+1;
		tmp_epilogis=table_label[epilogi];
		count_epilogis=0;
		while(tmp_epilogis!=NULL)  {	//Count how many labels the lexicographical max vertice has
			tmp_epilogis=tmp_epilogis->next;	//for comparing with others that they also have the same number of labels
			count_epilogis++;
		}
		for(j=0;j<vertices;j++)  {	//Check for founding equals lexicographical vertices
			tmp_epilogis=table_label[epilogi];
			count_elegxou=0;
			if(table_korifon[j]!=-1 && j!=epilogi)  {
				tmp_elegxou=table_label[j];
				while(tmp_elegxou!=NULL && tmp_epilogis!=NULL)  {	//Found equals vertices
					if(tmp_elegxou->epigrafi==tmp_epilogis->epigrafi)
						count_elegxou++;
					tmp_elegxou=tmp_elegxou->next;
					tmp_epilogis=tmp_epilogis->next;
				}
				if(count_epilogis==count_elegxou)  {	//Check and write in table all the equals
					count_pinaka++;
					pinakas[count_pinaka]=j+1;
				}
			}
		}
		int thesi1=0;
		int max1=0;
		for(j=0;j<=count_pinaka;j++)  {	//Found the vertice which is further to the right in sigma
			l=pinakas[j];
			thesi1=table_s[l-1];
			if(thesi1>max1)  {
				max1=thesi1;
				epilogi=l-1;
			}
		}
		count_pinaka=0;
		sigma_plus[count]=epilogi+1;
		for(j=0;j<vertices;j++)  {
			if(epilogi+1==table_korifon[j])  {
				table_korifon[j]=-1;
			}
		}
		tmp1=table[epilogi];
		while(tmp1!=NULL)  {	//Create labels for neighbours
			x=tmp1->vertex;
			flag=0;
			for(j=0;j<vertices;j++)  {
				if(sigma_plus[j]==x)
					flag=1;
			}
			if(flag==0)  {
				tmp2=(LABEL*)malloc(sizeof(LABEL));
				tmp2->epigrafi=i;
				tmp2->next=NULL;
				if(table_label[x-1]==NULL)
					table_label[x-1]=tmp2;
				else  {
					tmp3=table_label[x-1];
					while(tmp3->next!=NULL)
						tmp3=tmp3->next;
					tmp3->next=tmp2;
				}
			}
			tmp1=tmp1->next;
		}
		count++;
		epilogi=1;
		flag2=0;
		while(flag2==0)  {	//Bring random vertice out of sigma+ for check lexicographical max
			flag2=1;
			for(j=0;j<count;j++)  {
				if(sigma_plus[j]==epilogi)  {
					flag2=0;
					epilogi++;
				}
			}
		}
		epilogi--;
	}
	if(call==1)  {	//If first call return sigma+
		printf("σ+:\t");	//and print it
		s_return_plus=(int*)malloc(vertices*sizeof(int));
		for(i=0;i<vertices;i++)  {
			printf("%d  ",sigma_plus[i]);
			s_return_plus[i]=sigma_plus[i];
		}
	}
	else if(call==2)  {	//Otherwise return sigma++
		printf("σ++:\t");	//and print it
		s_return_plus_plus=(int*)malloc(sizeof(int));
		for(i=0;i<vertices;i++)  {
			printf("%d  ",sigma_plus[i]);
			s_return_plus_plus[i]=sigma_plus[i];
		}
	}
	printf("\n\n");
	free(tmp);
	free(tmp1);
	free(tmp2);
	free(tmp3);
}

void LBFS_MUL(LIST *table[],int *s_return_plus,int *s_return_plus_plus)  {

	int p,i,j,l,m,x,sigma_mul[vertices],flag=0,epilogi=s_return_plus_plus[vertices-1],flag_epilogi=0,count=1,flag2,count2,n,table_korifon[vertices],table_plus[vertices],table_plus_plus[vertices];
	int katastasi_a=-1,katastasi_b=-1,count_list_a,count_list_b,count_sigrisis_a=0,count_sigrisis_b=0,a,b;
	LABEL *tmp,*tmp2,*tmp3,*table_label[vertices],*epil_1,*epil_2;
	LIST *tmp1,*tmp_a,*tmp_b;
	int pinakas[vertices],count_epilogis,count_elegxou,count_pinaka=0;
	LABEL *tmp_epilogis,*tmp_elegxou;

	for(i=0;i<vertices;i++)  {	//Initialize sigma=-1
		sigma_mul[i]=-1;
		table_korifon[i]=i+1;
	}
	for(i=0;i<vertices;i++)  {
		for(j=0;j<vertices;j++)  {
			if(s_return_plus[j]==i+1)  {
				table_plus[i]=j+1;
			}
			if(s_return_plus_plus[j]==i+1)  {
				table_plus_plus[i]=j+1;
			}
		}
	}
	epilogi--;
	tmp=(LABEL*)malloc(sizeof(LABEL));	//Set the random vertice label equals to vertices number
	tmp->epigrafi=vertices;
	tmp->next=NULL;
	table_label[epilogi]=tmp;
	for(i=0;i<vertices;i++)  {	//Set all the other vertices label to NULL
		if(i!=epilogi)
			table_label[i]=NULL;
	}
	for(i=vertices;i>=1;i--)  {	//Like LBFS to found the lexicographical max
		for(m=0;m<vertices;m++)  {
			if(table_korifon[m]!=-1)  {
				epil_1=table_label[epilogi];
				epil_2=table_label[m];
				while(epil_1!=NULL && epil_2!=NULL && flag_epilogi==0)  {
					if(epil_1->epigrafi > epil_2->epigrafi)  {
						flag_epilogi=1;
					}
					else if(epil_1->epigrafi < epil_2->epigrafi)  {
						epilogi=m;
						flag_epilogi=1;
					}
					else  {
						epil_1=epil_1->next;
						epil_2=epil_2->next;
					}
				}
				if(flag_epilogi==0 && epil_1==NULL && epil_2!=NULL)  {
					epilogi=m;
				}
				flag_epilogi=0;
			}
		}
		for(j=0;j<vertices;j++)  {	//Initialize table that contains the equals vertices to 0
			pinakas[j]=0;
		}
		pinakas[count_pinaka]=epilogi+1;
		tmp_epilogis=table_label[epilogi];
		count_epilogis=0;
		while(tmp_epilogis!=NULL)  {
			tmp_epilogis=tmp_epilogis->next;	//Count the labels that the max vertice lexicographical has
			count_epilogis++;
		}
		for(j=0;j<vertices;j++)  {			//Check for vertices with the same label's number
			tmp_epilogis=table_label[epilogi];
			count_elegxou=0;
			if(table_korifon[j]!=-1 && j!=epilogi)  {
				tmp_elegxou=table_label[j];
				while(tmp_elegxou!=NULL && tmp_epilogis!=NULL)  {
					if(tmp_elegxou->epigrafi==tmp_epilogis->epigrafi)	//Found equals vertices
						count_elegxou++;
					tmp_elegxou=tmp_elegxou->next;
					tmp_epilogis=tmp_epilogis->next;
				}
				if(count_epilogis==count_elegxou)  {	//Check and put in a table all the equals vertces
					count_pinaka++;
					pinakas[count_pinaka]=j+1;
				}
			}
		}
		if(count_pinaka==0)  {	//If the table with all the equals vertices has only one entry then pick this one
			a=epilogi+1;
			b=epilogi+1;
		}
		else  {
			int thesi1=0;
			int max1=0;
			for(j=0;j<=count_pinaka;j++)  {	//Otherwise found a which is the max vertice lexicographical on the right of sigma+
				l=pinakas[j];
				thesi1=table_plus[l-1];
				if(thesi1>max1)  {
					max1=thesi1;
					a=l;
				}
			}
			int thesi2=0;
			int max2=0;
			for(j=0;j<=count_pinaka;j++)  {	//Found b which is the max vertice lexicographical on the right of sigma++
				l=pinakas[j];
				thesi2=table_plus_plus[l-1];
				if(thesi2>max2)  {
					max2=thesi2;
					b=l;
				}
			}
			count_pinaka=0;
		}
		if(a==b)  {
			epilogi=a-1;
		}
		else  {	//Check for F,NF,OK
			count_list_a=0;
			count_list_b=0;
			count_sigrisis_a=0;
			count_sigrisis_b=0;
			for(p=0;p<count;p++)  {	//Check for a
				tmp_a=table[a-1];
				while(tmp_a!=NULL)  {
					count_list_a++;
					if(tmp_a->vertex==sigma_mul[p])  {
						count_sigrisis_a++;
					}
					tmp_a=tmp_a->next;
				}
			}
			count_list_a=count_list_a/count;
			if(count_list_a!=count_sigrisis_a)  {
				katastasi_a=0;
			}
			else  {
				count_list_a=0;
				tmp_a=table[a-1];
				while(tmp_a!=NULL)  {
					if(tmp_a->vertex==b)  {
						count_sigrisis_b=0;
						for(p=0;p<count;p++)  {
							tmp_b=table[b-1];
							while(tmp_b!=NULL)  {
								count_list_b++;
								if(tmp_b->vertex==sigma_mul[p])  {
									count_sigrisis_b++;
								}
								tmp_b=tmp_b->next;
							}
						}
						count_list_b=count_list_b/count;
						if(count_list_b!=count_sigrisis_b)  {
							katastasi_a=1;
						}
					}
					tmp_a=tmp_a->next;
				}
			}
			if(katastasi_a==-1)  {
				katastasi_a=2;
			}
			count_list_a=0;	//check for b
			count_list_b=0;
			count_sigrisis_a=0;
			count_sigrisis_b=0;
			for(p=0;p<count;p++)  {
				tmp_b=table[b-1];
				while(tmp_b!=NULL)  {
					count_list_b++;
					if(tmp_b->vertex==sigma_mul[p])  {
						count_sigrisis_b++;
					}
					tmp_b=tmp_b->next;
				}
			}
			count_list_b=count_list_b/count;
			if(count_list_b!=count_sigrisis_b)  {
				katastasi_b=0;
			}
			else  {
				count_list_b=0;
				tmp_b=table[b-1];
				while(tmp_b!=NULL)  {
					if(tmp_b->vertex==a)  {
						count_sigrisis_a=0;
						for(p=0;p<count;p++)  {
							tmp_a=table[a-1];
							while(tmp_a!=NULL)  {
								count_list_a++;
								if(tmp_a->vertex==sigma_mul[p])  {
									count_sigrisis_a++;
								}
								tmp_a=tmp_a->next;
							}
						}
						if(count!=0)
							count_list_a=count_list_a/count;
						if(count_list_a==count_sigrisis_a)  {
							katastasi_b=1;
						}
					}
					tmp_b=tmp_b->next;
				}
			}
			if(katastasi_b==-1)  {
				katastasi_b=2;
			}
			if((katastasi_a==0 && katastasi_b==0) || (katastasi_a==0 && katastasi_b==1) || (katastasi_a==0 && katastasi_b==2) || (katastasi_a==1 && katastasi_b==1) || (katastasi_a==1 && katastasi_b==2) || (katastasi_a==2 && katastasi_b==2))  {
				epilogi=b-1;
			}
			else  {
				epilogi=a-1;
			}
		}
		katastasi_a=-1;
		katastasi_b=-1;
		sigma_mul[count-1]=epilogi+1;
		for(j=0;j<vertices;j++)  {
			if(epilogi+1==table_korifon[j])  {
				table_korifon[j]=-1;
			}
		}
		tmp1=table[epilogi];
		while(tmp1!=NULL)  {	//Create labels for all neighbours vertices
			x=tmp1->vertex;
			flag=0;
			for(j=0;j<vertices;j++)  {
				if(sigma_mul[j]==x)
					flag=1;
			}
			if(flag==0)  {
				tmp2=(LABEL*)malloc(sizeof(LABEL));
				tmp2->epigrafi=i;
				tmp2->next=NULL;
				if(table_label[x-1]==NULL)
					table_label[x-1]=tmp2;
				else  {
					tmp3=table_label[x-1];
					while(tmp3->next!=NULL)
						tmp3=tmp3->next;
					tmp3->next=tmp2;
				}
			}
			tmp1=tmp1->next;
		}
		count++;
		epilogi=1;
		flag2=0;
		while(flag2==0)  {	//Take a random vertice which not belong in sigma*
			flag2=1;
			for(j=0;j<count-1;j++)  {
				if(sigma_mul[j]==epilogi)  {
					flag2=0;
					epilogi++;
				}
			}
		}
		epilogi--;
	}
	printf("σ*:\t");
	s_return_mul=(int*)malloc(vertices*sizeof(int));
	for(i=0;i<vertices;i++)  {
		printf("%d  ",sigma_mul[i]);
		s_return_mul[i]=sigma_mul[i];
	}
	printf("\n\n");
	free(tmp);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(tmp_a);
	free(tmp_b);
}

void is_umbrella_free(LIST *table[],int *s_return_mul)  {
	int i,j,table_n[vertices],flag=0,arxi,telos;
	LIST *tmp;

	for(i=0;i<vertices-1;i++)  {
		table_n[i]=0;
	}
	for(i=0;i<vertices-1;i++)  {
		for(j=i+1;j<vertices;j++)  {
			tmp=table[s_return_mul[i]-1];
			while(tmp!=NULL)  {
				if(tmp->vertex==s_return_mul[j])  {
					table_n[i]=j;
				}
				tmp=tmp->next;
			}
		}
	}
	table_n[vertices-1]=0;
	for(i=0;i<vertices;i++)  {
		for(j=i+1;j<table_n[i];j++)  {
			tmp=table[s_return_mul[i]-1];
			while(tmp!=NULL)  {
				if(tmp->vertex==s_return_mul[j])  {
					flag=1;
				}
				tmp=tmp->next;
			}
			if(flag==0)  {
				printf("The graph G is not interval graph.\n\n");
				exit(1);
			}
			flag=0;
		}
	}
	printf("The graph G is an interval graph and the interval model is:\n\n");
	for(i=1;i<=vertices;i++)  {
		arxi=3*i-1;
		if(table_n[i-1]==0)
			telos=3*i+1;
		else
			telos=3*(table_n[i-1]+1)+1;
		printf("%d: (%d,%d)\n",s_return_mul[i-1], arxi,telos);
	}
	printf("\n");
}

main() {
	int random_vertex;
	printf("Insert the number of the vertices: "); 
	scanf("%d", &vertices);
	printf("Insert the number of the edges: "); 
	scanf("%d", &edges);
	random_vertex=rand()%vertices+1;	//We take a random vertice for use it in LBFS
	LIST *table[vertices];				//Declare vertices table
	scan_edges(table,vertices,edges);	//Void for reading the graph's edges
	print_graph(table);					//Void for printing the graph
	LBFS(table,random_vertex);			//LBFS call
	call=1;								//For returning the sigma+
	LBFS_PLUS(table,s_return);			//LBFS+ call with sigma for returning sigma+
	call=2;								//For returning the sigma++
	LBFS_PLUS(table,s_return_plus);		//LBFS+ call with sigma+ for returning sigma++
	LBFS_MUL(table,s_return_plus,s_return_plus_plus);	//LBFS* call with sigma+ and sigma++ for returning sigma*
	is_umbrella_free(table,s_return_mul);			//Call for check that the graph is umbrella free
}
