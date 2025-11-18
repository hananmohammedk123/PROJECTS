#include <stdio.h>
#include "encode.h"
#include"decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    uint img_size;
    if(argc<3)
    {
        printf("few arguments passed\n");
        return 0;
    }
    else if(argc>=3 && argc <=5)
    {
        if(check_operation_type(argv)==e_encode)
        {
            if(read_and_validate_encode_args(argc,argv,&encInfo)==e_failure)
            {
                 printf("encoding failed\n");
                return 0;
            }
            else if(do_encoding(&encInfo)==e_success)
            {
                printf("data encoded\n");
            }
            else
            {
                printf("encoding failed\n");
                return 0;
            }           
        }
        else if(check_operation_type(argv)==e_decode)
        {
            if(read_and_validate_decode_args(argc,argv,&decInfo)==e_failure)
            {
                 printf("decoding failed\n");
                return 0;
            }
            else if(do_decoding(&decInfo)==e_success)
            {
                printf("decoding completed\n");
            }
            else
            {
                printf("Decoding failed\n");
                return 0;
            }  
        }
        else if(check_operation_type(argv)==e_unsupported)
        {
            printf("invalid argument passed\nDemo is as shown => ");
            printf("./a.out [-e/-d] beuatiful.bmp secret.txt filename.bmp\n");
        }
        
    }
    else
    {
        printf("More number of arguments passed\n");
    }
    return 0;

}
