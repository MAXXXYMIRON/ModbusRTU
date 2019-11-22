#include<stdio.h>
#include<locale.h>
#include<stdlib.h>

main()
{
	setlocale(0, "");

	_asm
	{
		Polynom db 0b10110110   
		B1 db 00h               
		B2 db 00h				
		BReceiver db 00h        
		Counter db 0x08			

		call ReceiverData       
		mov B1, BReceiver       
		jmp FOR					

		CRC:					
		mov cl, 8				
		FOR_CRC: 
		cmp cl, 0
		je END_CRC
		dec cl	

		shr B2, 1               
		shr B1, 1               
		jnc FOR_CRC             
		xor B1, Polynom         
		jmp FOR_CRC

		END_CRC:
		ret                     

		FOR:					
		dec Counter				
		call ReceiverData       
		mov B2, BReceiver       
		call CRC                
		cmp Counter, 1          
		jne FOR                 
	}	

	system("pause");
}