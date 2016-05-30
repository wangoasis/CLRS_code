#include "redBlackTree.h"
#include <stdio.h>

#define N 50

int main( )
{
    rbTree T;
    position P;
    int i;
    int j = 0;

    T = init( );
    T = makeEmpty( T );

    for( i = 1; i < N; i++ ) 
        T = insert( i, T );
    printf( "Inserts are complete\n" );

    printTree(T);

    printf("\nroot value is %d\n", retrieve(T));

    for( i = 1; i < N; i++ )
        if( ( P = find( i, T ) ) == NULL || retrieve( P ) != i )
            printf( "Error at %d\n", i );

    printf( "Min is %d, Max is %d\n", retrieve( findMin( T ) ),
               retrieve( findMax(T)));

    for( i = 16 ; i > 0; i -= 2) {
        T = delete(i, T);
        printf("\n");
    }

    printTree(T);

    printf( "\nMin is %d, Max is %d\n", retrieve( findMin( T ) ),
               retrieve( findMax( T ) ) );

    return 0;
}
