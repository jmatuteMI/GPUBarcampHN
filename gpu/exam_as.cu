
__global__ void add(int a,int b,int *c){
  *c = a+b;
}

int main(){
  int c;
  int *resp;

  cudaMalloc( (void**)&resp,sizeof(int));

  add<<<1,1>>>(2,3,resp);

  cudaMemcpy(&c,resp,sizeof(int),cudaMemcpyDeviceToHost);

  cudaFree(resp);

  return c;
}
