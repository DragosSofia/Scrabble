#include <stdio.h>
#include <string.h>
#include "util/scrabble.h"

int convert_char_to_int( char numar[ 10 ] ) 
{
  int nr = 0 ;

  for( int i = 0 ; numar[ i ] >= '0' && numar[ i ] <= '9' ; i++ )
  {
    nr *= 10 ;
    nr += numar[ i ] - '0' ;
  }  

  return nr ;

}

void put_vertical(char game_board [ 15 ][ 15 ] , int x , int y , char cuvant[ 17 ])
{
  int lg  ;
  lg = strlen( cuvant );

  for( int i = 0 ; i < lg ; i++ )
        game_board[ x + i ][ y ] = cuvant[ i ] ;
}

void put_orizontal(char game_board [ 15 ][ 15 ] , int x , int y , char cuvant[ 17 ])
{
  int lg  ;
  lg = strlen( cuvant );

  for( int i = 0 ; i < lg  ; i++ )
        game_board[ x ][ y + i ] = cuvant[ i ];
      
}

void do_task_1 ( char game_board[ 15 ][ 15 ] , char lista_cuv[ 20 ][ 17 ] , int *nr_cuv )
{
  int nr , x , y , d , i , j , lg_cuv , ct = 0  ;
  char *p , comanda[ 100 ] , cuvant[ 16 ] , n[ 10 ] , aux[ 16 ] ;

  //citim numarul de cuvinte 
  fgets( n , 10 , stdin ) ;

  nr = convert_char_to_int( n ) ;
  
  for( i = 1 ; i <= nr ; i ++ )
  {
    fgets( comanda , 100 , stdin ); //citim instructiunea/comanda 

    //preluam y 
    p = strtok( comanda , " \n" );  
    strcpy( aux , p ) ;
    y = convert_char_to_int( aux ); 

    //preluam x 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    x = convert_char_to_int( aux );

    //preluam d 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    d = convert_char_to_int( aux );  

    //preluam cuvantul 
    p = strtok( NULL , " \n" );
    strcpy( cuvant , p );
    lg_cuv = strlen( cuvant );

    //adaugam cuvantul la lista de cuvinte
    strcpy( lista_cuv[ ct ++ ] , cuvant );
    

    if( d == 0 )
      put_orizontal( game_board , y , x , cuvant);
    else
      put_vertical( game_board , y , x , cuvant);
  }

  *nr_cuv = nr ;
  

}

int pct_cuv( char cuv[ 16 ] )
{
  int i , ct = 0 ;

  for( i = 0 ;  cuv[ i ] != 0 ; i++ )
  {
    ct ++ ; 
    if( strchr( "DG" , cuv[ i ] ) != NULL )
        ct ++ ;
    if( strchr( "BCMP" , cuv[ i ] ) != NULL )
        ct += 2 ; 
    if( strchr( "FHVWY" , cuv[ i ] ) != NULL )
        ct += 3 ;
    if( cuv[ i ] == 'K' )
        ct += 4 ; 
    if( strchr( "JX" , cuv[ i ] ) != NULL )
        ct += 7 ;
    if( strchr( "QZ" , cuv[ i ] ) != NULL )
        ct += 9 ;
  }

  return ct ;
}

void do_task_2 ( char game_board[ 15 ][ 15 ] )
{
  
  char comanda[ 100 ] , *p , aux[ 16 ] , cuvant[ 16 ] , n[ 10 ];
  int y , x , d , W=0 , T=0 , i ,nr ; 
  //citim numarul de cuvinte 
  fgets( n , 10 , stdin ) ;

  nr = convert_char_to_int( n ) ;
  
  for( i = 1 ; i <= nr ; i ++ )
  {
    fgets( comanda , 100 , stdin ); //citim comanda 

    //preluam y 
    p = strtok( comanda , " \n" );  
    strcpy( aux , p ) ;
    y = convert_char_to_int( aux ); 

    //preluam x 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    x = convert_char_to_int( aux );

    //preluam d 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    d = convert_char_to_int( aux );  

    //preluam cuvantul 
    p = strtok( NULL , " \n" );
    strcpy( cuvant , p );
    
    //adaugam punctele la plaerul care trebuie
    if( i % 2 == 1 )
      W += pct_cuv( cuvant );
    else
      T += pct_cuv( cuvant );
  }

  printf( "Player 1: %d Points\n" , W );
  printf( "Player 2: %d Points\n" , T );

}

int pct ( char game_board[ 15 ][ 15 ] , int y , int x , int d , char cuvant[ 17 ] , int XX[4] , int YY[4] )
{ 
  int gasit_XX , gasit_YY , bonus = 1 , nr_lit , j  ; 

  //cautam subsirul XX in cuvant
    if( strstr( cuvant , XX ) != NULL )
        gasit_XX = 1 ;
    else
        gasit_XX = 0 ;
     
    // verificam daca cuvantul se termina in YY
    nr_lit = strlen( cuvant );
    if( strcmp( cuvant + nr_lit - 2 , YY ) == 0 )
      gasit_YY = 1 ;
    else
      gasit_YY = 0 ; 
    
    //calculam bonusul 
    if( d == 0 )
        for( j = 0 ; j < nr_lit ; j++ )
            {
              if( bonus_board[ y ][ x + j ] == 1 && gasit_XX == 1 )
                  bonus *= 2 ;
              if( bonus_board[ y ][ x + j ] == 2 && gasit_YY == 1 )
                  bonus *= 3 ;  
            }
    else
      for( j = 0 ; j < nr_lit ; j++ )
            {
              if( bonus_board[ y + j ][ x ] == 1 && gasit_XX == 1 )
                  bonus *= 2 ;
              if( bonus_board[ y + j ][ x ] == 2 && gasit_YY == 1 )
                  bonus *= 3 ;  
            }

    
    return bonus * pct_cuv( cuvant ) ;
}


void do_task_3 ( char game_board[ 15 ][ 15 ] )
{
  
  char comanda[ 100 ] , *p , aux[ 16 ] , cuvant[ 16 ] , n[ 10 ] , XX[ 4 ] , YY[ 4 ]; 
  int y , x , d , W=0 , T=0 , i , j ,nr , poz , bonus , gasit_XX , gasit_YY , nr_lit , a ; 

  fgets( XX , 4 , stdin );
  XX[ 2 ] = NULL ;

  fgets( YY , 4 , stdin );
  YY[ 2 ] = NULL ;

  //citim numarul de cuvinte 
  fgets( n , 10 , stdin ) ;
  nr = convert_char_to_int( n ) ;
  
  for( i = 1 ; i <= nr ; i ++ )
  { 

    bonus = 1 ;

    fgets( comanda , 100 , stdin ); //citim comanda 

    //preluam y 
    p = strtok( comanda , " \n" );  
    strcpy( aux , p ) ;
    y = convert_char_to_int( aux ); 

    //preluam x 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    x = convert_char_to_int( aux );

    //preluam d 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    d = convert_char_to_int( aux );  

    //preluam cuvantul 
    p = strtok( NULL , " \n" );
    strcpy( cuvant , p );
    
    //adaugam punctele la plaerul care trebuie
    a = pct( game_board , y , x , d , cuvant , XX , YY );
   
    if( i % 2 == 1 )
      W += a ;
    else
      T += a ;


  }

  printf( "Player 1: %d Points\n" , W );
  printf( "Player 2: %d Points\n" , T );

}


int put_word_orizontal ( char game_board [ 15 ][ 15 ] , int x , int y , char cuvant[ 17 ] )
{ 
  int lg ,  ok ;
  lg = strlen( cuvant );

  // verificam daca incape in matrice pe orizontal
  if( y + lg - 1 > 14 )
      return 0 ;

  // verificam daca putem sa il punem orizontal
  ok = 1 ;
  for( int i = y + 1 ; i < y + lg - 1 && ok == 1 ; i++ )
      if( game_board[ x ][ i ] != '.' )
          ok = 0 ;
  
  return ok ;
}

int put_word_vertical ( char game_board [ 15 ][ 15 ] , int x , int y , char cuvant[ 17 ] )
{
  int lg ,  ok ;
  lg = strlen( cuvant );

  //verificam daca incape pe verticala
  if( x + lg - 1 > 14 )
      return 0 ;
  
   //verificam daca putem sa il punem pe verticala
  ok = 1 ;
  for( int i = x + 1 ; i < x + lg  && ok == 1 ; i++ )
      if( game_board[ i ][ y ] != '.' )
          ok = 0 ;
  
  return ok ;
}

void do_task_4 ( char game_board[ 15 ][ 15 ] )
{
  char XX[ 5 ] ,YY[ 5 ] ;
  char list_cuv[ 20 ][ 17 ];
  char cuvant[ 17 ];
  int nr_cuv , gata = 0 , gasit = 0 , lg ;
  int i , j , k ;

  fgets( XX , 4 , stdin );
  XX[ 2 ] = 0 ;

  fgets( YY , 4 , stdin );
  YY[ 2 ] = 0 ;

  do_task_1( game_board , list_cuv , &nr_cuv );
  
  for( k = 0 ; k < 100 && gata == 0 ; k++ )
  { 
    lg = strlen( words[ k ] );

    //cautam cuvantul in lista de cuvinte deja puse
    gasit = 0 ;
    for( i = 0 ; i < nr_cuv && gasit == 0 ; i++ )
      if( strcmp( words[ k ] , list_cuv[ i ] ) == 0  )
          gasit = 1 ;
    
    //daca nu este deja pus
    if( gasit == 0 )
    { 
      //cautam un loc in cae sa il punem
      for( i = 0 ; i < 15  && gata == 0 ; i ++ )
        for( j = 0 ; j < 15  && gata == 0 ; j ++ )
            if( game_board[ i ][ j ] == words[ k ][ 0 ] )  //daca gasim prima litera a cuvantului
              {
                //incercam sa il punem pe orizontal deoarece are prioritate maxima
               if( put_word_orizontal( game_board , i , j , words[ k ]  ) == 1  ) 
                  {
                   put_orizontal( game_board , i , j , words[ k ] );
                   gata = 1 ;
                  }
                // in cazul in care nu reusim incercam sa il punem pe vertical
                if( gata == 0 && put_word_vertical( game_board , i , j , words[ k ]  ) == 1  ) 
                  {
                   put_vertical( game_board , i , j , words[ k ] );
                   gata = 1 ;
                  }
              }
    }
  }
      
  print_board( game_board );
}

void do_task_5( char game_board[ 15 ][ 15 ] )
{
  char XX[ 5 ] ,YY[ 5 ] , n[ 10 ] ;
  char list_cuv[ 20 ][ 17 ] , comanda[ 100 ]; 
  char cuvant[ 17 ] , *p , aux[ 17 ] , lista_cuv[ 20 ][ 17 ] ;
  int nr_cuv , gata = 0 , gasit = 0 , lg , nr , x , y , d , W = 0 , T = 0 ;
  int maxi = 0 , xmaxi , ymaxi , dmaxi , lg_cuv , ct = 0 ;
  char cuv_maxi[16];
  int i , j , k ;

  fgets( XX , 4 , stdin );
  XX[ 2 ] = 0 ;

  fgets( YY , 4 , stdin );
  YY[ 2 ] = 0 ; 

  //citim numarul de cuvinte 
  fgets( n , 10 , stdin ) ;

  nr = convert_char_to_int( n ) ;
  
  for( i = 1 ; i <= nr ; i ++ )
  {
    fgets( comanda , 100 , stdin ); //citim comanda 

    //preluam y 
    p = strtok( comanda , " \n" );  
    strcpy( aux , p ) ;
    y = convert_char_to_int( aux ); 

    //preluam x 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    x = convert_char_to_int( aux );

    //preluam d 
    p = strtok( NULL , " \n" );
    strcpy( aux , p ) ;
    d = convert_char_to_int( aux );  

    //preluam cuvantul 
    p = strtok( NULL , " \n" );
    strcpy( cuvant , p );
    lg_cuv = strlen( cuvant );

    //adaugam cuvantul la lista de cuvinte
    strcpy( lista_cuv[ ct ++ ] , cuvant );
    

    if( d == 0 )
      put_orizontal( game_board , y , x , cuvant);
    else
      put_vertical( game_board , y , x , cuvant);

    //adaugam punctajul fiecarui jucator
    if( i % 2 == 1 )
      W += pct( game_board , y , x , d , cuvant , XX , YY ) ;
    else
      T+= pct( game_board , y , x , d , cuvant , XX , YY ) ;

  }

  for( k = 0 ; k < 100 && gata == 0 ; k++ )
  { 
    lg = strlen( words[ k ] );

    //cautam cuvantul in lista de cuvinte deja puse
    gasit = 0 ;
    for( i = 0 ; i < ct && gasit == 0 ; i++ )
      if( strcmp( words[ k ] , list_cuv[ i ] ) == 0  )
          gasit = 1 ;
    
    //daca nu este deja pus poate concura pt punctajul maxim
    if( gasit == 0 )
    { 
      //cautam un loc in cae sa il punem
      for( i = 0 ; i < 15  ; i ++ )
        for( j = 0 ; j < 15   ; j ++ )
            if( game_board[ i ][ j ] == words[ k ][ 0 ] )  //daca gasim prima litera a cuvantului
              {
                //incercam sa il punem pe orizontal  si ne da cel mai mare punctaj pana la pasul curent il tinem minte in maxim
               if( put_word_orizontal( game_board , i , j , words[ k ]  ) == 1 && pct( game_board , i , j , 0 , words[ k ] , XX , YY ) >= maxi  ) 
                  {
                   maxi = pct( game_board , i , j , 0 , words[ k ] , XX , YY ) ;
                   xmaxi = j ;
                   ymaxi = i ;
                   dmaxi = 0 ;
                   strcpy( cuv_maxi , words[ k ] );
                  }
                //incercam sa il punem pe verticala  si ne da cel mai mare punctaj pana la pasul curent il tinem minte in maxim
                if( put_word_vertical( game_board , i , j , words[ k ]  ) == 1 && pct( game_board , i , j , 0 , words[ k ] , XX , YY) >= maxi  ) 
                  {
                   maxi = pct( game_board , i , j , 0 , words[ k ] , XX , YY) ;
                   xmaxi = j ;
                   ymaxi = i ;
                   dmaxi = 1 ;
                   strcpy( cuv_maxi , words[ k ] );
                  }
              }
    }
  }
    //daca nu reusim sa obtinem punctaj mai mare decat Player 1 
    if( maxi < W - T )
        printf( "Fail!");
    else // altfel adaugam cuvantul din maxim in matrice
    {
      if( dmaxi == 0 )
        put_orizontal( game_board , ymaxi , xmaxi , cuv_maxi );
      else
        put_vertical( game_board , ymaxi , xmaxi , cuv_maxi );

    print_board( game_board );
    }


}

int main()
{
  char task[100] ;
  char game_board [ 15 ] [ 15 ] , lista_cuv[ 20 ][ 17 ]  ;
  int nr_cuv ;

  fgets( task , 100 , stdin );
  
  memset ( game_board , '.' , 15 * 15 );

  // task 0 
  if( task[ 0 ] == '0' )
  {
    print_board( game_board ) ;
  }
  
  //task 1
  if( task[ 0 ] == '1' ) 
  {
    //parametrii list_cuv is nr_cuv ii vom folosi la taskul 4 
    do_task_1( game_board , lista_cuv , &nr_cuv );
    print_board( game_board ) ;
  }

  //task 2
  if( task[ 0 ] == '2' )
  {
    do_task_2( game_board );
  }

  //task3
  if( task[ 0 ] == '3' )
  {
    do_task_3( game_board );
  }

  //task4
  if( task[0] == '4' )
  {
    do_task_4( game_board );
  }

  //
  if( task [ 0 ] == '5' )
  {
    do_task_5( game_board );
  }
}