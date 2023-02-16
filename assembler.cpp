#include<bits/stdc++.h>
using namespace std;

#define R_TYPE 0
#define L_TYPE 1
#define S_TYPE 2
#define BEQ_TYPE 3
#define BNEQ_TYPE 4
#define J_TYPE 6
#define I_TYPE 8

int PC=0;


class Parser{
    private :
     vector<string> INSTRUCTION;
    public: 
        uint32_t parse( string instruction){

            string temp="";

            for(int i=0;i<instruction.length();i++){

                if(instruction[i]!=',' && instruction[i]!=' ' && instruction[i]!='(' && instruction[i]!=')' ){
                    temp+=instruction[i];
                }
                else{
                    if(temp!=""){
                        INSTRUCTION.push_back(temp);
                    }
                    temp="";
                }
            }

            INSTRUCTION.push_back(temp);
            return assemble();
        }

        uint32_t assemble(){      // instruction to binary
                
            // INSTRUCTION--> ADD R1 R2 R3

            uint32_t bit_by_bit=0;

            uint32_t Op=-1 , Rs, Rt, Rd, Shamt=2, Funct_field=0, offset, immediate_value=0;

            for( int i = 0; i < 1 ; i++ ){

                if( INSTRUCTION[i]=="ADD" || INSTRUCTION[i]=="SUB" || INSTRUCTION[i]=="AND" ||  INSTRUCTION[i]=="MUL" || INSTRUCTION[i]=="SLT" ){
                    Op=R_TYPE;
                }

                if( INSTRUCTION[i]=="LW" ){
                    Op=L_TYPE;
                }

                if(INSTRUCTION[i]=="SW"){
                    Op=S_TYPE;
                }

                if( INSTRUCTION[i]=="BEQ" ){
                    Op=BEQ_TYPE;
                }

                if( INSTRUCTION[i]=="BNEQ" ){
                    Op=BNEQ_TYPE;
                }

                if( INSTRUCTION[i]=="J" ){
                    Op=J_TYPE;
                }

                if( INSTRUCTION[i]=="ADDI" ){
                    Op=I_TYPE;
                }

            }

            if( Op==R_TYPE){

                // rs rt rd

                int len = INSTRUCTION[1].length();

                if(len==2){

                    Rs=INSTRUCTION[1][1]-48;

                }
                else{

                    Rs=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);

                }

                len = INSTRUCTION[2].length();

                if(len==2){

                    Rt=INSTRUCTION[2][1]-48;

                }
                else{

                    Rt=10*(INSTRUCTION[2][1]-48)+(INSTRUCTION[2][2]-48);
                    
                }

                len = INSTRUCTION[3].length();

                if(len==2){

                    Rd=INSTRUCTION[3][1]-48;

                }
                else{

                    Rd=10*(INSTRUCTION[3][1]-48)+(INSTRUCTION[3][2]-48);
                    
                }

                // funct field

                if(INSTRUCTION[0]=="ADD"){
                    Funct_field=1;
                }
                else if(INSTRUCTION[0]=="SUB"){
                    Funct_field=2;
                }
                else if(INSTRUCTION[0]=="MUL"){
                    Funct_field=3;
                }
                else if(INSTRUCTION[0]=="AND"){
                    Funct_field=4;
                }
                else if(INSTRUCTION[0]=="SLT"){
                    Funct_field=5;
                }

            }

            else if(Op==L_TYPE){

                // rt= destiantion register
                // lw $1,100($2)
                // vector-> lw $1 100 $2
                int len = INSTRUCTION[1].length();

                if(len==2){
                    Rt=INSTRUCTION[1][1]-48;
                }
                else{
                    Rt=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);
                }

                //uint32_t offset = 0;
                uint32_t times=INSTRUCTION[2].length();

                while(times--){
                    
                    offset+=(uint32_t)pow(10,times-1)*(INSTRUCTION[2][times-1]-48);  // offset = number in 32 bit

                }

                 len = INSTRUCTION[3].length();

                if(len==2){
                    Rs=INSTRUCTION[3][1]-48;
                }
                else{
                    Rs=10*(INSTRUCTION[3][1]-48)+(INSTRUCTION[3][2]-48);
                }

            }

            else if(Op==S_TYPE){

                // rs= destiantion register
                // rt = src register
                // sw $1,100($2)
                // vector-> sw $1 100 $2
                int len = INSTRUCTION[1].length();

                if(len==2){
                    Rs=INSTRUCTION[1][1]-48;
                }
                else{
                    Rs=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);
                }

                //uint32_t offset = 0;
                uint32_t times=INSTRUCTION[2].length();

                while(times--){
                    
                    offset+=(uint32_t)pow(10,times-1)*(INSTRUCTION[2][times-1]-48);  // offset = number in 32 bit

                }

                len = INSTRUCTION[3].length();

                if(len==2){
                    Rt=INSTRUCTION[3][1]-48;
                }
                else{
                    Rt=10*(INSTRUCTION[3][1]-48)+(INSTRUCTION[3][2]-48);
                }

            }

            else if(Op==BEQ_TYPE){
                // beq $1,$2,104
                
                int len = INSTRUCTION[1].length();

                if(len==2){
                    Rs=INSTRUCTION[1][1]-48;
                }
                else{
                    Rs=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);
                }

                 len = INSTRUCTION[2].length();

                if(len==2){
                    Rt=INSTRUCTION[2][1]-48;
                }
                else{
                    Rt=10*(INSTRUCTION[2][1]-48)+(INSTRUCTION[2][2]-48);
                }

                uint32_t times=INSTRUCTION[2].length();

                while(times--){
                    
                    offset+=(uint32_t)pow(10,times-1)*(INSTRUCTION[2][times-1]-48);  // offset = number in 32 bit

                }

            }

            else if(Op==BNEQ_TYPE){

                // bneq $1,$2,104
                
                int len = INSTRUCTION[1].length();

                if(len==2){
                    Rs=INSTRUCTION[1][1]-48;
                }
                else{
                    Rs=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);
                }

                 len = INSTRUCTION[2].length();

                if(len==2){
                    Rt=INSTRUCTION[2][1]-48;
                }
                else{
                    Rt=10*(INSTRUCTION[2][1]-48)+(INSTRUCTION[2][2]-48);
                }

                uint32_t times=INSTRUCTION[2].length();

                while(times--){
                    
                    offset+=(uint32_t)pow(10,times-1)*(INSTRUCTION[2][times-1]-48);  // offset = number in 32 bit

                }

            }

            else if(Op==J_TYPE){

                // j 1000

                uint32_t times=INSTRUCTION[2].length();

                while(times--){
                    
                    offset+=(uint32_t)pow(10,times-1)*(INSTRUCTION[2][times-1]-48);  // offset = number in 32 bit

                }

            }

            else if(Op==I_TYPE){

                // addi $1,$2,69
                // vector-> addi $1 $2 69
                // rs=destination  rt=source1   imm_value



                int times = INSTRUCTION[3].length();

                while(times--){

                    immediate_value+=(uint32_t)pow(10,times-1)*(INSTRUCTION[3][times-1]-48);

                }

                int len = INSTRUCTION[1].length();

                if(len==2){
                    Rs=INSTRUCTION[1][1]-48;
                }
                else{
                    Rs=10*(INSTRUCTION[1][1]-48)+(INSTRUCTION[1][2]-48);
                }

                len = INSTRUCTION[2].length();

                if(len==2){
                    Rt=INSTRUCTION[2][1]-48;
                }
                else{
                    Rt=10*(INSTRUCTION[2][1]-48)+(INSTRUCTION[2][2]-48);
                }

            }

            // setting bits of
            // uint32_t bit_by_bit=0;

            if(Op==R_TYPE){

                // 31-26 = Op   25-21=Rs   20-16=Rt   15-11=Rd    10-6=shamt   5-0=funct

                bit_by_bit|=(Op<<26);
                
                bit_by_bit|=(Rs<<21);

                bit_by_bit|=(Rt<<16);

                bit_by_bit|=(Rd<<11);

                bit_by_bit|=(Shamt<<6);

                bit_by_bit|=(Funct_field<<0);

                // bit_by_bit = 32 bit instruction for R type

            }

            else if(Op==L_TYPE){

                // 31-26   25-21   20-16   15-0

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(Rs<<21); 

                bit_by_bit|=(Rt<<16);

                bit_by_bit|=(offset<<0);

            }

            else if(Op==S_TYPE){

                // 31-26   25-21   20-16   15-0

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(Rs<<21); 

                bit_by_bit|=(Rt<<16);

                bit_by_bit|=(offset<<0);

            }

            else if(Op==BEQ_TYPE){

                // 31-26   25-21   20-16   15-0

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(Rs<<21); 

                bit_by_bit|=(Rt<<16);

                bit_by_bit|=(offset<<0);

            }

            else if(Op==BNEQ_TYPE){

                // 31-26   25-21   20-16   15-0

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(Rs<<21); 

                bit_by_bit|=(Rt<<16);

                bit_by_bit|=(offset<<0);

            }

            else if(Op==J_TYPE){

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(offset<<0);

            }

            else if(Op==I_TYPE){

                bit_by_bit|=(Op<<26);

                bit_by_bit|=(Rs<<21);

                bit_by_bit|=(Rs<<16);

                bit_by_bit|=(immediate_value<<0);
            }

            
            
            return bit_by_bit;    // final 32-bit instruction

        }
};
class Fetch{
    public: 
      string instruction;
       // for handing space after instruction mode

       uint32_t fetch_instruction(string INST){   
            
        instruction=INST;     // instruction memory
            // instrcution=value at PC
            // instruction is now set to the string ie eg-> ADD,R1,R2,R3
           return  update_PC();
        }    

        uint32_t update_PC(){
            PC = PC + 1 ;
            
           // INSTRUCTION.clear();
            Parser* ins = new Parser();
            return ins->parse(instruction);
        }
};

int main()
{
        ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("assembly.txt", "r", stdin);
    freopen("instruction.mem", "w", stdout);
#endif
    vector<string> bin_inst;
    while(true){
        string instruction;
        getline(cin,instruction);
        if(instruction == "END")  break;
        Fetch* fet = new Fetch();
        string m="";
        uint32_t f = fet->fetch_instruction(instruction);
        for(int i =0;i<32;i++){
            if((f&(1<<i))!=0)
                m+="1";
            
            else 
                m+="0";
            }
            reverse(m.begin(),m.end());
            bin_inst.push_back(m);
    }
    for(auto i : bin_inst){
        cout<<i<<"\n";
    }
}