Custom snprintf alternative. 

Work in progress. 

It just needs support for scientific notation decimals, hexadecimal floats,
and some new features, namely pointers so you can interpolate values without the need for varying arguments, and possibly regex so you can extract matches from an address/varying argument strings. 
The function doesn't send the result to the output buffer like printf does, but returns it instead. 
