int main(){
    int a,b;
    while(a==1){
        a+1;
        b=a+b;
    }
    if(b){
        continue;;
    }else{
        return;
    }
    callMyFunction(a+1,b-2);
}