public class fibonacci
{
	public static final int TOTAL = 8 ;
	public static void main( String[ ] args )
	{
		float[] arr = new float[ TOTAL ] ;
		for (int i = 0 ; i < TOTAL ; i++)
			arr[ i ] = fib(i) ;

		for (int i = 0 ; i < TOTAL ; i++)
			System.out.println( arr[ i ] ) ;
	}
	/* retorna elemento i da s�rie 1,1,2,3,5,8,... */
	public static int fib( int i )
	{
		if (i < 1 )		/* inv�lido */
			return 0 ;
		else if (i == 1 || i == 2)
			return 1 ;
		else
			return fib( i -2 ) + fib(i - 1) ;
	}
}
