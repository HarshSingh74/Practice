#include<stdio.h>
void fcfs(int[],int);
void sjf(int[],int);
void rr(int[],int);
int Q1BT[10],q1size=0,Q2BT[10],q2size=0,Q3BT[10],q3size=0; 
int main()
{
    int i,ch,bt; 
    printf("**********Multi-level Queue process Scheduling**********");
    do
	{
    	printf("\nSelect type of process :\n1)System Process\n2)Batch Process\n3)User Process\n4)No process left\nPriority : ");
    	scanf("%d",&ch);
        switch (ch)
        	{
        		case 1	:   q1size++;
							printf("\nEnter burst time for SYSTEM process %d:",q1size);
							scanf("%d",&Q1BT[q1size-1]);
							break;
        		case 2	:   q2size++;
							printf("\nEnter burst time for BATCH process %d:",q2size);
							scanf("%d",&Q2BT[q2size-1]);
							break;
        		case 3	:   q3size++;
							printf("\nEnter burst time for USER process %d:",q3size);
							scanf("%d",&Q3BT[q3size-1]);
							break;
        		case 4	:   break;				
        		default	:   printf("**Wrong Choice!!!!");
							break;
			}
    }while(ch!=4);
    
    
    if(q1size)
    {
    	printf("\n\nSYSTEM Process queue : FCFS\n");
    	fcfs(Q1BT,q1size);   	
	}
    return 0;
}
void fcfs(int BT[],int n)
{
	
	float AWT=0, ATAT=0;
	int wt=0,i;
	for(i=0;i<n-1;i++)
	{
		wt=wt+BT[i];
		AWT=AWT+wt;
	}
	AWT=AWT/n;
	printf("\nAverage Wait Time:%f",AWT);
	wt=0;
	for(i=0;i<n;i++)
	{
		wt=wt+BT[i];
		ATAT=ATAT+wt;
	}
	ATAT=ATAT/n;
	printf("\nAverage Turn Around Time:%f",ATAT);
	if(q2size)
    {
		printf("\n\nBATCH Process queue : SJF\n");
		sjf(Q2BT,q2size);
	}
	else
	{
		printf("\n\nUSER Process queue : Round Robin\n");
		rr(Q3BT,q3size);
	}
}

//SJF
void sjf(int BT[],int n)
{
    float AWT=0, ATAT=0;
	int wt=0,i,j,temp;

	for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (BT[j] > BT[j+1])
            {
                temp=BT[j];
                BT[j]=BT[j+1];
                BT[j+1]=temp;
            }
        }
    }

	for(i=0;i<n-1;i++)
	{
		wt=wt+BT[i];
		AWT=AWT+wt;
	}
	AWT=AWT/n;
	printf("\nAverage Wait Time\t:%f",AWT);
	wt=0;
	for(i=0;i<n;i++)
	{
		wt=wt+BT[i];
		ATAT=ATAT+wt;

	}
	ATAT=ATAT/n;
	printf("\nAverage Turn Around Time:%f",ATAT);
	
	if(q3size)
	{
		printf("\n\nUSER Process queue : Round Robin\n");
		rr(Q3BT,q3size);
	}
}

//ROUND ROBIN
void rr(int BT[],int n)
{
	float AWT, ATAT;
	int WT[n];
	int TAT[n];
	int rembt[n];
	int t=0;
	int i,j,quantum,count=0,done=1;
    if(q3size)
    {
		AWT=0;
		ATAT=0;
		for(i=0;i<n;i++)
	    {
	        WT[i]=0;
	    }
	    for(i=0;i<n;i++)
	    {
	        TAT[i]=0;
	    }
	    for(i=0;i<n;i++)
	    {
	        rembt[i]=BT[i];
	    }
		printf("Enter time quantum : ");
		scanf("%d",&quantum);
	    count = 0;
	    while(1)
	    {
	        done=1;
	        for(i=0;i<n;i++)
	        {
	            if(rembt[i]>0)
	            {
	                done=0;
	                if(rembt[i]>quantum)
	                {
						t=t+quantum;
						rembt[i]=rembt[i]-quantum;}
	                else
	                {t=t+rembt[i];
	               WT[i]=t-BT[i];
	                 rembt[i]=0;
	                }
	            }
	        }
	        if(done==1)
	        {
	            break;
	        }
	    }
	    for(i=0;i<n;i++)
	    {
	        TAT[i]=BT[i]+WT[i];
	    }
	    for(i=0;i<n;i++)
	    {
	        AWT=AWT+WT[i];
	        ATAT += TAT[i];
	    }

	    AWT=AWT/n;
		printf("\nAverage Wait Time\t:%f",AWT);
		
		ATAT=ATAT/n;
		printf("\nAverage Turn Around Time:%f",ATAT);
}
}
