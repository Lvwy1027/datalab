/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~ ( x & y ) & ~ ( ~ x & ~ y ) ;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
	if ( ( ! x ) && ( ! y ) )
		return 1 ;  //x和y两个是0
	if ( ! ( x && y ) )
		return 0 ;  //x和y一个是0 
	return ( ! ( ( x ^ y ) & 0x80000000 ) ) ;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b1 = ( v > 65535 ) << 4 ;
    v = v >> b1 ;
    int b2 = ( v > 255 ) << 3 ;
    v = v >> b2 ;
    int b3 = ( v > 15 ) << 2 ;
    v = v >> b3 ;
    int b4 = ( v > 3 ) << 1 ;
    v = v >> b4 ;
    int b5 = ( v > 1 ) ;
	return b1 | b2 | b3 | b4 | b5 ;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int M = m << 3;
	int N = n << 3;
	int M2 = 0x000000ff << M ;
	int N2 = 0x000000ff << N ;
	int b = ( x >> M << N ) & N2 ;
	int c = ( x >> N << M ) & M2 ;
	return ( x & ( ~ M2 ) & ( ~ N2 ) ) | b | c ;  
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned b = ( v >> 0b10000 ) | ( v << 0b10000 ) ;
	unsigned c = ( ( b >> 0b1000 ) & 0b00000000111111110000000011111111 ) | 
	( ( b << 0b1000 ) & 0b11111111000000001111111100000000 ) ;
	unsigned d = ( ( c >> 0b100 ) & 0b00001111000011110000111100001111 ) | 
	( ( c << 0b100 ) & 0b11110000111100001111000011110000 ) ;
	unsigned e = ( ( d >> 0b10 ) & 0b00110011001100110011001100110011 ) | 
	( ( d << 0b10 ) & 0b11001100110011001100110011001100 ) ;
	unsigned f = ( ( e >> 0b1 ) & 0b01010101010101010101010101010101 ) | 
	( ( e << 0b1 ) & 0b10101010101010101010101010101010 ) ;
    return f;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
	int n0 = ~ n + 32;  //31-n
	return ( ~ ( 0xffffffff << 1 << n0 ) ) & ( x >> n ) ;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
   	int p = ! ( x ^ 0xffffffff ) ;
	
	int b1 = ! ( ~ ( x & 0xffff0000 ) >> 16 ) ;  //判断前16位是否全为1
	b1 = b1 << 4 ; 
	x = x << b1 ;  //如果全为1，b1=16，看后16位，否则看前16位
	 
	int b2 = ! ( ~ ( x & 0xff000000 ) >> 24 ) ;
	b2 = b2 << 3; 
	x = x << b2 ;
	
	int b3 = ! ( ~ ( x & 0xf0000000 ) >> 28 ) ;
	b3 = b3 << 2 ;
	x = x << b3 ;
	
	int b4 = ! ( ~ ( x & 0xc0000000 ) >> 30 ) ;
	b4 = b4 << 1 ;
	x = x << b4 ;
	
	int b5 = ! ( ~ ( x & 0x80000000 ) >> 31 ) ;
	x = x << b5 ;

	return ( b1 | b2 | b3 | b4 | b5 ) + p ;
	
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
	if( ! x )
		return x ;  //x=0的情况 
 
	int result = 0 ; 
	if ( x < 0 ){  
		x = - x ;
		result = 0x80000000 ;
	}  //调正负号 
	
	int y = x ; 
	int digit = 0 ;  //找第一位1在哪 末位为第0位 
	
	int t = 16 ;
	while ( t ){
		if ( y & ( 0xffffffff ) << ( 32 - t ) )
			digit = digit + t ;
		else 
			y = y << t ;
		t = t >> 1 ;
	}
	
	/*
	if( y & 0xffff0000 )
		digit = digit + 16 ;
	else
		y = y << 16 ;
	
	if( y & 0xff000000 )
		digit = digit + 8 ;
	else
		y = y << 8 ;

	if( y & 0xf0000000 )
		digit = digit + 4 ;
	else
		y = y << 4 ;
	
	if( y & 0xc0000000 )
		digit = digit + 2 ;
	else
		y = y << 2 ;
	
	if( y & 0x80000000 )
		digit = digit + 1 ;
	else
		y = y << 1 ;
	*/
	int z = x ;	
	int digit0 = digit - 23 ;
	
	if(digit < 24)
		z = ( z << ( - digit0 ) ) ;
	else
		z = ( z >> digit0 ) ;  
	z = z & 0x007fffff ;  //求尾码
	
	if ( digit > 23 ) {
		int s = x << ( 54 - digit ) & 0x7fffffff ;
		int lar = s - 0x40000000 ; 
		
		if ( ( lar > 0 ) | ( ( lar == 0 ) & ( z & 1 ) ) )
			z = z + 1 ; 
				
	}  //四舍五入，向偶数舍入 
	
	digit = digit + 127 ;  //加偏移量 阶码 
	
	result = result + ( digit << 23 ) + z ;
    return result ;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
	unsigned sign = uf & 0x80000000 ;  //第一位 正负号
	unsigned jie = uf >> 23 & 0x000000ff ;
	unsigned wei = uf & 0x007fffff ;
	if ( jie == 0 )
		return ( wei + wei ) | sign ;  //阶码全为0
	if ( jie == 255 )
		return uf ;
	jie = jie + 1 ;
	if ( jie == 255 )
		return 0x7f800000 | sign ;
	return ( jie << 23 ) | sign | wei ; 
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    /*
	if ( ! ( uf2 + uf1 ) )  //表示0 
		return 0 ;
	
	unsigned sign = uf2 & 0x80000000 ;
	int jie = uf2 >> 22 & 0x1ff ;  //double的阶码
	jie = jie - 255 ;  //减去偏移量
	
	unsigned wei = uf2 & 0x003fffff ; 
	 
	if ( jie > 127 )
		return 0x7f800000 | sign ;  //绝对值太大
	if ( jie < -149)
		return 0 ;  //绝对值太小 
	
	if ( jie < -126 ){
		unsigned t = 149 + jie ;  //t表示float里的首位 
		wei = uf2 >> ( 22 - t ) | 1 << t ;  //需要将uf2的第22位填1，并且将uf2的22-0位挪到(149+jie)(t)至0的位置 //22-t为移动位数 
		jie = 0 ;
		
		int she = uf2 & ~ ( 0xffffffff << ( 22 - t ) ) ; //uf2中被舍去的为最后的22-(149+jie)即(-jie-127)位 
		
		if ( she > 1 << ( 21 - t ) ) {  //she和 uf2被舍去部分仅最高位为1的数 比较大小 
		
			wei = wei + 1 ;
			if ( wei >> 23 ) {
				jie = jie + 1 ; 
				wei = wei & 0x007fffff ;
			}
		}
		
		if ( ! ( she - 1 << ( 21 - t ) ) ) {  //uf2的部分一样 
		
			if ( uf1 > 0 ){
				wei = wei + 1 ;
				if ( wei >> 23 ){
					jie = jie + 1 ;
					wei = wei & 0x007fffff ;
				}
			}
			
			if ( ( ! uf1 ) & ( wei & 1 ) ){
				wei = wei + 1 ;
				if ( wei >> 23 ){
					jie = jie + 1 ;
					wei = wei & 0x007fffff ;
				}
			}
				
		}
		return ( jie + 127 ) << 23 | wei | sign ;
	}
	
	wei = ( uf2 << 1 & 0x007f0000 ) | ( uf1 & 0x80000000 ) >> 31  ;
	
	unsigned she = uf1 & 0x7fffffff ;
	if ( she > 0x40000000 ) {
		wei = wei + 1 ;
		if ( wei >> 23 ){
			jie = jie + 1 ;
			wei = wei & 0x007fffff ;
		}
	}
	if ( ! ( she - 0x40000000 ) ) {
		if ( wei & 1 ){
			wei = wei + 1 ;
			if ( wei >> 23 ){
				jie = jie + 1 ;
				wei = wei & 0x007fffff ;
			}
		}
	}	
	if( ! ( jie - 128 ) )
		return 0x7f800000 | sign ;
	return ( jie + 127 ) << 23 | wei | sign ;	 
	
	*/
	
	//////////////////////
	/*
	int result = 0x80000000 & uf2 ;  //正负号 
	int sign = result ;
	
	if ( ! ( ( uf2 & 0x7fffffff ) - 0x3fc00000 ) & ! uf1 ) { //表示1
		if ( sign )
			return -1 ;
		else
			return 1 ;
		}
	
	int a = ( uf2 >> 22 ) & 0x1ff ;
	a = a - 255 ;  //2的指数 
	if ( a > 30 )
		return 0x80000000 ;
	if ( a < 0 )
		return 0x00000000 ;
	if ( ! a ) {  // a=0
		if ( sign )	
			return -1 ;
		else
			return 1 ;
	}
		
	result = result | ( 1 << a ) ;
	
	if ( a >= 22 ){
		uf1 = uf1 >> ( 54 - a ) ;
		uf2 = ( uf2 & 0x3fffff ) << ( a - 22 ) ;
		result = result | uf1 | uf2 ;
	}
	else{
		uf2 = ( uf2 & 0x3fffff ) >> ( 22 - a ) ;
		result = result | uf2 ;
	}
	
	if ( sign )
		result = - ( result | 0x7fffffff ) ;
	
	return result;
	*/
	unsigned sign = uf2 & 0x80000000 ;
    int jie = ( uf2 >> 20 ) & 0x7ff ;
    
    unsigned wei = ( ( uf2 & 0xfffff ) << 11 ) + ( ( uf1 >> 21 ) & 0x7ff ); // uf2的低20位+uf1的高11位
    
	jie = jie - 1023 ;
	if ( jie > 30 )
        return 0x80000000;
    if ( jie < 0 )
        return 0;
    
    int jie0 = 31 - jie ;
    wei = wei | 0x80000000 ;
    wei = ( wei >> jie0 ) & ( ~ ( 0x80000000 >> jie0 << 1 ) ) ; // 避免算数右移导致的前导1
    if ( sign )
        return - wei ;
    return wei ;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if ( x < -149 )
    	return 0 ;
    	
    if ( x < -126 )
    	return 1 << ( x + 149 ) ;
    	
    if ( x < 128 )
    	return ( x + 127 ) << 23 ;
    
    return 0x7f800000 ;
}
