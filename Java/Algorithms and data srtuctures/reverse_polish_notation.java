//Natalia Durlik 
import java.util.Scanner;
public class Source {
	public static int maxSize=256;
	public static String out="";//answer
	public static String s="";//input
	public static boolean INF=false;
	public static void main(String[] args){
		
		int k=in.nextInt();
		in.nextLine();
	 for(int i=0;i<k;i++)
	 {
		s="";
		out="";
		s=in.nextLine();
		INF=false;
		if(s.charAt(0)=='I') INF=true;
		usuwanieNiedoskonalosci();
		if(INF) 
		{
			if(automatINF())
			{
				shuntingYard();//inf to onp
				System.out.println("ONP: "+out);
			}
			else System.out.println("ONP: error");
		}
		else //0NP
		{
			if(automatONP())
			{
				RPNtoINF();//onp to inf
				System.out.println("INF: "+out);
			}
			else System.out.println("INF: error");
		}
	 }
	}
	public static void usuwanieNiedoskonalosci()
	{
		char[] schar=s.toCharArray();
		int count=0;
		for(int i=0;i<schar.length;i++)
		{       //litera 
			char el=schar[i];
			if( (el>=97&&el<=122) || 
					isOperator(el) ||  
				((el=='('||el==')')&&INF==true) )//jesli poprawne
			{
				schar[count]=el;
				count++;
			}
		}
		//array to string again
		StringBuilder sb = new StringBuilder();
		for (int i=0;i<count;i++) 
		{
			sb.append(schar[i]);
		}
		s = sb.toString();//nadpisujemy
	//	System.out.println(s);
	}
	public static void shuntingYard()
	{
		arrayCharStack charStack=new arrayCharStack(maxSize);
		int i=0;
		do
		{
			char el=s.charAt(i);
			if(el>=97&&el<=122)// litera
			{
				out+=el;
			}
			else//operator lub nawias
			{
				if(el!='('&&el!=')')//operator
				{
					if(!charStack.isEmpty()&&charStack.top()!='(')//bo ')' nigdy nie wsadzamy
					{
						while(charStack.top()!='('&&((isLeft(el)&&prior(charStack.top())>=prior(el))||(!isLeft(el)&&prior(charStack.top())>prior(el))))
						{
							out+=charStack.pop();
						}
					}
					charStack.push(el);
				}
				else if(el=='(') charStack.push(el);//FIXME do gory tego ifa
				else if(el==')')
				{
					while(charStack.top()!='('&&!charStack.isEmpty())
					{
						out+=charStack.pop();
					}
					charStack.pop();//wyrzucamy(
				}
				else System.out.println("nic");
			}
			
			i++;
		}while(i<s.length());
		while(!charStack.isEmpty())
		{
			out+=charStack.pop();
		}
	}
	public static void RPNtoINF()
	{
		arrayStringStack strStack=new arrayStringStack(maxSize);
		arrayIntStack intStack=new arrayIntStack(maxSize);
		String supp="";
		int i=0;
		do
		{
			char el=s.charAt(i);
			if(el>=97&&el<=122)
			{
				strStack.push(""+el);
				intStack.push(prior(el));
			}
			else //jakis operator
			{
				supp="";
				String op2=strStack.pop();
				if(el!='~')//FIXME, dac do left
				{
					String op1=strStack.pop();//potrzeba drugiego operanda
					if(isLeft(el))
					{
						if(!intStack.isEmpty()&&intStack.top()<=prior(el)) supp="("+op2+")";
						else supp=op2;
						intStack.pop();
						if(!intStack.isEmpty()&&intStack.top()<prior(el)) supp="("+op1+")"+el+supp;
						else supp=op1+el+supp;
					}
					else//lacznosc prawostronna, tzn na odwrot do 
					{
						if(!intStack.isEmpty()&&intStack.top()<prior(el)) supp="("+op2+")";
						else supp=op2;
						intStack.pop();
						if(!intStack.isEmpty()&&intStack.top()<=prior(el)) supp="("+op1+")"+el+supp;
						else supp=op1+el+supp;
					}
				}
				else//operator unarny, 
				{
					if(!intStack.isEmpty()&&intStack.top()<prior(el)) supp=el+"("+op2+")";
					else supp=el+op2;
				}
				intStack.pop();
				strStack.push(supp);
				intStack.push(prior(el));
			}
			i++;
		}while(i<s.length());
		out=strStack.top();
	}
	
	public static boolean isOperator(char el)
	{
		if(el=='='||el=='<'||el=='>'||el=='+'||el=='-'||el=='*'||el=='/'||el=='%'||el=='^'||el=='~') return true;
		else return false;
	}
	public static boolean automatINF()
	{
		//litery, operatory, nawiasy
		//w tym '~' jednoargumentowy
		
		int parenthesis=0;
		int operands=0;
		int operators=0;
		int state=0;//rozpoczescie analizy od 1 symbolu
		for(int i=0;i<s.length();i++)
		{
			char el=s.charAt(i);
			switch(state)//FIXME
			{//sprawdza poprawna kolejsc nastepujacychpo sobie znakow
			
			case 0://q0
				if(el=='(') parenthesis++;
				else if(el>=97&&el<=122)
				{
					operands++;
					state=1;
				}
				else if((isOperator(el)&&el!='~')||el==')') return false;//samo els wystarczy chyba
				else if(el=='~') state=2;// bo moze byc ~a
				break;
				
			case 1://q1
				if(el==')') parenthesis--;
				else if(isOperator(el)&&el!='~')
				{
					operators++;
					state=0;
				}
				else if((el>=97&&el<=122)||el=='~'||el=='(') return false;//bo 2 litery pod rzad
				break;
				
			case 2://q2
				//if(el=='~~')//to nic,~, tyld ile chcemy
				if(el=='(') 
				{
					state=0;
					parenthesis++;
				}
				else if(el>=97&&el<=122) 
				{
					operands++;
					state=1;
				}
				else if((isOperator(el)&&el!='~')||el==')') return false;
				break;
			}
			if(parenthesis<0) return false;
		}
		if(parenthesis!=0||operators!=operands-1) return false;
		return true;
	}
	public static boolean automatONP()
	{
		//liczby lub operatory, bez nawiasów
		int operators=0;
		int operands=0;
	//	int tylda=0;
		if(s.charAt(0)=='~') return false;
		for(int i=0;i<s.length();i++)
		{
			char el=s.charAt(i);
			if(el>=97&&el<=122)//litera
			{
				operands++;
			}
			else if(el!='~')//operator
			{
				operators++;
			}
			if(operands<=operators) return false;
		}
		if(operators!=operands-1) return false;
		return true;
	}
	
	public static int prior(char op)
	{
		if(op=='0') return -1;//pop&top
		if(op=='=') return 0;
		else if(op=='<'||op=='>') return 1;//lewy
		else if(op=='+'||op=='-') return 2;//lewy
		else if(op=='*'||op=='/'||op=='%') return 3;//lewy
		else if(op=='^') return 4;
		else if(op=='~') return 5;
		else return 6;//do rpn->inf
	}
	public static boolean isLeft(char op)//lacznosc
	{
		if(op=='*'||op=='/'||op=='%'||op=='>'||op=='<'||op=='+'||op=='-') return true;
		else return false;
	}
	public static Scanner in=new Scanner(System.in);
}

class arrayCharStack {
	private int maxSize;
	private char[] Stack;
	private int top;
    public arrayCharStack(int maxSize) {
    	this.maxSize=maxSize;
    	this.Stack=new char[maxSize];
    	top=maxSize;
    }
    public boolean isEmpty() {
        if(top==maxSize) return true;
        return false;
    }
    public boolean isFull() {
    	if(top==0) return true;
        return false;
    }
    public int numberOfElements() {
        return maxSize-top;
    }
    public void push(char x) {
    	if(!isFull())
    	{
    		top--;
    		Stack[top]=x;
    	}
    }
    public char top() {
    	if(!isEmpty())
    	{
    		return Stack[top];
    	}
    	else return '0';
    }
    public char pop() {
    	if(!isEmpty())
    	{
    		top++;
    		return Stack[top-1];
    	}
        return '0';
    } 
    public void show(){
    	if(!isEmpty())
    	{
    		for(int i=maxSize-1;i>=top;i--)
    		{
    			System.out.print(Stack[i]+" ");
    		}
	   //     System.out.println();
    	}
    }
    //fa62f759fa58416bffd53770dff31c35
}
class arrayIntStack {
	private int maxSize;
	private int[] Stack;
	private int top;
    public arrayIntStack(int maxSize) {
    	this.maxSize=maxSize;
    	this.Stack=new int[maxSize];
    	top=maxSize;
    }
    public boolean isEmpty() {
        if(top==maxSize) return true;
        return false;
    }
    public boolean isFull() {
    	if(top==0) return true;
        return false;
    }
    public int numberOfElements() {
        return maxSize-top;
    }
    public void push(int x) {
    	if(!isFull())
    	{
    		top--;
    		Stack[top]=x;
    	}
    }
    public int top() {
    	if(!isEmpty())
    	{
    		return Stack[top];
    	}
    	else return 0;
    }
    public int pop() {
    	if(!isEmpty())
    	{
    		top++;
    		return Stack[top-1];
    	}
        return 0;
    } 
    public void show(){
    	if(!isEmpty())
    	{
    		for(int i=maxSize-1;i>=top;i--)
    		{
    			System.out.print(Stack[i]+" ");
    		}
	   //     System.out.println();
    	}
    }
}

class arrayStringStack {
	private int maxSize;
	private String[] Stack;
	private int top;
    public arrayStringStack(int maxSize) {
    	this.maxSize=maxSize;
    	this.Stack=new String[maxSize];
    	top=maxSize;
    }
    public boolean isEmpty() {
        if(top==maxSize) return true;
        return false;
    }
    public boolean isFull() {
    	if(top==0) return true;
        return false;
    }
    public int numberOfElements() {
        return maxSize-top;
    }
    public void push(String x) {
    	if(!isFull())
    	{
    		top--;
    		Stack[top]=x;
    	}
    }
    public String top() {
    	if(!isEmpty())
    	{
    		return Stack[top];
    	}
    	else return "0";
    }
    public String pop() {
    	if(!isEmpty())
    	{
    		top++;
    		return Stack[top-1];
    	}
        return "0";
    } 
    public void show(){
    	if(!isEmpty())
    	{
    		for(int i=maxSize-1;i>=top;i--)
    		{
    			System.out.print(Stack[i]+" ");
    		}
	   //     System.out.println();
    	}
    }
    
}