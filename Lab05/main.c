#include <stdio.h>
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "xbram_hw.h"
void	write_data(u32 address, u32 data1 , u32 data2);



int main()
{
	u32	data;
	int a0, a1, a2, a3;
	int b0, b1, b2, b3;
	u32 a0u, a1u, a2u, a3u;
	u32 b0u, b1u, b2u, b3u;
	u32 command;
	int count = 0;
	u32 cmd_left, cmd_right;
	u32 n=1;

    print("Program Start...\n");

	while(getchar() != EOF) {

		printf("Input command +(1) -(2) x(3) T(4) det(5):");
				scanf("%d", &command);
				printf(" %d\r\n", command);
				if(command > 5 || command < 1){
				printf("Error with command\n");
					continue;
				}
		if((command != 4 )||(command != 5 ) ){
		printf("Please input numbers that less than 63 (-64~63)\n");
		printf("Input a0:");
		scanf("%d", &a0);
		printf(" %d\r\n", a0);
		printf("Input a1:");
		scanf("%d", &a1);
		printf(" %d\r\n", a1);
		printf("Input a2:");
		scanf("%d", &a2);
		printf(" %d\r\n", a2);
		printf("Input a3:");
		scanf("%d", &a3);
		printf(" %d\r\n", a3);
		printf("Input b0:");
		scanf("%d", &b0);
		printf(" %d\r\n", b0);
		printf("Input b1:");
		scanf("%d", &b1);
		printf(" %d\r\n", b1);
		printf("Input b2:");
		scanf("%d", &b2);
		printf(" %d\r\n", b2);
		printf("Input b3:");
		scanf("%d", &b3);
		printf(" %d\r\n", b3);

		}
		else{
			printf("Please input numbers that less than 63 (-64~63)\n");
			printf("Input a0:");
			scanf("%d", &a0);
			printf(" %d\r\n", a0);
			printf("Input a1:");
			scanf("%d", &a1);
			printf(" %d\r\n", a1);
			printf("Input a2:");
			scanf("%d", &a2);
			printf(" %d\r\n", a2);
			printf("Input a3:");
			scanf("%d", &a3);
			printf(" %d\r\n", a3);
			b0 = 0;
			b1 = 0;
			b2 = 0;
			b3 = 0;
		}

		a0u = a0 & 127;
		a1u = a1 & 127;
		a2u = a2 & 127;
		a3u = a3 & 127;
		b0u = b0 & 127;
		b1u = b1 & 127;
		b2u = b2 & 127;
		b3u = b3 & 127;

		cmd_right = a0u + (a1u << 7) + (a2u << 14) + (a3u << 21) + (b0u << 28);
		cmd_left  = (b0u >> 4) + (b1u << 3) + (b2u << 10) + (b3u << 17);
		cmd_left  = cmd_left + (n << (23 + command));
		write_data(XPAR_BRAM_0_BASEADDR+count*64+32 ,cmd_right,cmd_left);


		printf("Finish input?yes(1) no(0)");
				scanf("%d", &command);
				printf(" %d\r\n", command);
				if(command==1){
					XBram_WriteReg(XPAR_BRAM_0_BASEADDR ,0,2147483648);
					break;
				}
				else {
					count ++;
				}

	}
	for(int i=0 ; i< 1000000000; i++){			}
	for(int i=0 ; i< count+1 ;i++){
		command = XBram_ReadReg(XPAR_BRAM_0_BASEADDR + 1280, i*8);
		a0 = command & 127;
		a1 = (command >> 7) & 127;
		a2 = (command >> 14) & 127;
		a3 = (command >> 21) & 127;
		printf("a0 = %d  \na1 = %d\na2 = %d\na3 = %d\n", a0,a1,a2,a3);

	}
	for(int i=0 ; i< 256 ;i++){
		command = XBram_ReadReg(XPAR_BRAM_0_BASEADDR+i*32, 0);
		if(command != 0) {
			printf("data = %d  i = %d\n", command, i);
		}

	}
	print("Program End...\n");


    return 0;
}

void	write_data(u32 address, u32 data1 , u32 data2 )
{

	XBram_WriteReg(address, 0 , data1);	//cmd	write
	XBram_WriteReg(address+32, 0 , data2);	//data_in

}




