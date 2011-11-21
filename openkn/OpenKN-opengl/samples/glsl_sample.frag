
void main(void)
{
  vec4 color = vec4(1.0,0.0,0.0,1.0);
  
  float size = 0.5;
  /*
  float tmpx = gl_TexCoord[0].x * 2.0;
  float tmpy = gl_TexCoord[0].y * 2.0;
  
  if(mod(tmpx,0.1) < size || mod(tmpy,0.1) < size)
    color.rgb = vec3(0.0,0.0,0.0);

*/
  
  
  float tmpy = gl_TexCoord[0].y * 3.141592654 * 10.0;
  float tmpx = gl_TexCoord[0].x * 10.0 * (1.0+size);
  float subx = mod(tmpx,2.0*(1.0+size)) - 1.0 - size;
  if(subx-size<sin(tmpy) && subx+size>sin(tmpy)){
    float tmp = abs(subx - sin(tmpy));
    float inter = smoothstep(size*0.6,size,tmp);
    color.rgb = vec3(inter)*color.rgb;
  }
  
  gl_FragColor = color;
}

