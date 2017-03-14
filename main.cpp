#include <stdio.h>
#include "configure.h"

void CNN (TYPE_T *input, TYPE_T *weight1, TYPE_T *bias1, TYPE_T *conv1_out);

int main()
{
    TYPE_T *input = new TYPE_T[227*227*3];
    FILE *fp=fopen("/Users/tqy/Documents/cs 259/proj/cnn/cnn/input.txt","r");
    
    for(int i = 0;i < 227*227*3;i++)
    {
        if(fscanf(fp,"%f",&input[i])==EOF)
            break;
       // else printf ("%f\n", input[i]);
    }
    
    fclose(fp);
    //printf ("%f\n", *(input+3));
    TYPE_T *weight1 = new TYPE_T [11*11*3*96];
    fp=fopen("/Users/tqy/Documents/cs 259/proj/cnn/cnn/conv1_w_11_11_3_96.txt","r");
    for (int l = 0; l < 96;l++)
        for(int i = 0;i < 3;i++)
            for (int j = 0;j < 11; j++){
                for (int k = 0; k < 11;k++)
                {
                    if(fscanf(fp,"%f",&weight1[l*3*11*11+i*11*11+j*11+k])==EOF)
                        break;
                }
            }
    fclose(fp);
    
    TYPE_T bias1[96]={0};
    TYPE_T *conv1_out = new TYPE_T [55*55*96];

    CNN (input, weight1, bias1, conv1_out);
    delete[] input;
    delete[] weight1;
    delete[] conv1_out;
    
    return 0;
}
