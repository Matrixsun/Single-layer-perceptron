#include<stdio.h>
#include<stdlib.h>

int nTrain=7;  //训练样本数量
int nInput=3; //训练样本维度
double delta=0.1;  //学习速率
int nTest=1; //测试样本数量
int maxItre =100;
typedef struct slp {
	int input[3];
	int output;
} slp_testData;

double com_output( int *input,double *weight)
{
	double sum=0.0;
	for(int i=0;i <nInput;i++)
	{
		sum= sum + (input[i] * weight[i]);
	}
	sum=sum - weight[nInput]*1.0;
	return sum;
}


//分类函数
int classOutPerceptron(double output)
{
	if (output >= 0)
		return 1 ;
	if (output < 0 )
		return -1;
}

//计算误差
int com_err(slp_testData *trainData,double *weight)
{
	int err=0,i;
	for(i=0;i<nTrain;i++)
	{
		err = err+ trainData[i].output - classOutPerceptron(com_output(trainData[i].input,weight));
	}
	return err;
}

int main(void)
{
	int i ,j,k,tempResu ;
	slp_testData trainData[7]=    
	{
		{{1,0,0},-1},
		{{1,0,1},1},
		{{1,1,0},1},
		{{1,1,1},1},
		{{0,0,1},-1},
		{{0,1,0},-1},
		{{0,1,1},1},
	};
	slp_testData testData[1]=
	{
		{{0,0,0},-1},
	};
	double weights[4]={0.0,0.0,0.0,0.4};  //赋值权重，最后一位是偏移
	for(k=0;k<maxItre;k++)
	{
	for(i=0;i<nTrain;i++)
	{
		tempResu = classOutPerceptron(com_output(trainData[i].input,weights));
		
		for (j=0;j<nInput;j++)
		{
			weights[j] = weights[j] + ( delta*(trainData[i].output - tempResu)*trainData[i].input[j]);
		}
		weights[nInput] = weights[nInput] + delta*(trainData[i].output - tempResu);
	}
	}

	for (i=0;i<nTrain;i++)
        {
                printf("train[%d] .. %d\n",i,classOutPerceptron(com_output(trainData[i].input,weights)));
        }	

	for (i=0;i<nTest;i++)
	{
		printf("test[%d] .. %d\n",i,classOutPerceptron(com_output(testData[i].input,weights)));
	}
	return 0;
}
