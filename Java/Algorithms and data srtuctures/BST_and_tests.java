public class TestBST {
    public static void main(String[] args) {
		BST<Integer> tree = new BST<Integer>(9);
		tree.insertIter(11);
		tree.insertIter(5);
		tree.insertIter(4);
		tree.insertIter(5);
		tree.insertIter(5);
		tree.insertIter(10);
		System.out.println(tree.size());
	//	tree.display();
		
		/*tree.insertRec(11);
		tree.insertRec(5);
		tree.insertRec(4);
		tree.insertRec(5);
		tree.insertRec(5);
		tree.insertRec(10);*/
		
		tree.printInorderRec();
		tree.printInorder();
		
		/*tree.search(16);
		tree.searchFather(16);*/
	//	tree.search(10);
		//tree.searchFather(10);
		
	/*	tree.deleteElem(4);
		tree.printInorderRec();
		tree.printInorder();
		tree.deleteElem(5);
		tree.printInorderRec();
		tree.printInorder();
		System.out.println(tree.size());
		tree.deleteElem(10);
		tree.deleteElem(11);
		tree.deleteElem(5);
		tree.deleteElem(5);
		tree.printInorderRec();
		tree.printInorder();
		System.out.println(tree.size());
		tree.deleteElem(9);
		tree.printInorderRec();
		tree.printInorder();*/
		
		BST<Integer> tree2 = tree.cut(11);
		tree.printInorder();
		tree2.printInorder();
		
		
	}
}


/**
 * Binary Search Tree.
 */
class BST<T extends Comparable<T>> {
	Node<T> root;
	int size;
	int height;
	/**
	 * Tworzy puste drzewo binarne.
	 */
	public BST() {
		root=null;
		size=0;
	}
	/**
	 * Tworzy drzewo binarne z elementem root na pozycji korzenia.
	 */	
	public BST(T root_value) {
		root = new Node<T>(root_value);
		size=1;
	}
	/** 
	 * Wstawia element v do drzewa binarnego. Jeœli v ju¿ znajduje siê 
	 * w drzewie to nowy wêze³ nie jest tworzony, ale inkrementuje siê
	 * jego licznoœæ. 
	 */
	public void insertIter(T v) {
		size++;
		if(root!=null)
		{
			Node<T> p=root;
			Node<T> prev=root;
			while(p!=null&&p.value!=v)
			{
				prev=p;
				if(p.value.compareTo(v)>0) p=p.l;
				else p=p.r;
			}
			if(p==null)
			{
				if(prev.value.compareTo(v)>0) prev.l=new Node<T>(v);
				else prev.r=new Node<T>(v);
			}
			else p.count++;
		}
		else root=new Node<T>(v);
	}
	public void insertRec(T v) {
		size++;
		if(root==null) root=new Node<T>(v);
		else root=insertRecAux(root,v);
	}
	public Node<T> insertRecAux(Node<T> p,T v) {
		if(p!=null)
		{
			if(p.value.compareTo(v)>0) p.l=insertRecAux(p.l,v);
			else if(p.value.compareTo(v)<0) p.r=insertRecAux(p.r,v);
			else p.count++;
		}
		else p=new Node<T>(v);
		return p;
	}
	/**
	 * Usuwa jeden element v z drzewa.
	 */
	public void deleteElem(T v) {
		if(root.value.equals(v))
		{
			size--;
			if(root.l==null&&root.r==null) root=null;
			else if(root.l!=null&&root.r==null) root=root.l;
			else if(root.l==null&&root.r!=null) root=root.r;
			else //root.l!=null&&root.r!=null
			{
				Node<T> rs=root.r;
				Node<T> fs=rs;
				while(rs.l!=null) 
				{
					fs=rs;
					rs=rs.l;
				}
				root.value=rs.value;
				fs.l=rs.r;
			}
			return;
		}
		Node<T> q=searchFather(v);
		if(q==null) return;
		size--;
		boolean left=true;
		Node<T> p=q.l;
		if(q.r!=null&&q.r.value.equals(v)) 
		{
			p=q.r;
			left=false;
		}
		if(p.count==1)
		{
			if(p.l==null&&p.r==null) 
			{
				if(left) q.l=null;
				else q.r=null;
			}
			else if(p.l!=null&&p.r==null)
			{
				if(left) q.l=p.l;
				else q.r=p.l;
			}
			else if(p.r!=null&&p.l==null)
			{
				if(left) q.l=p.r;
				else q.r=p.r;
			}
			else //(p.r!=null&&p.l!=null)
			{
				Node<T> s=p.r;
				Node<T> f=s;
				while(s.l!=null)
				{
					f=s;
					s=s.l;
				}
				p.value=s.value;
				f.l=s.r;
			}
		}
		else p.count--;
	}
	/** 
	 * Zwraca wêze³ o wartoœci v.
	 */
	public Node<T> search(T v) {
		Node<T> p=root;
		while(p!=null&&p.value.compareTo(v)!=0)
		{
			if(p.value.compareTo(v)>0) p=p.l;
			else p=p.r;
		}
		if(p!=null ) {}//System.out.println("Search: "+v+" "+p.value);
		else System.out.println("Search: "+v+" nie ma");
		return p;
	}
	public Node<T> searchFather(T v) {
		if(root.value.equals(v)) 
		{
			//System.out.println("Dla "+v+" root:"+root.value);
			return root;
		}
		Node<T> p=root;
		Node<T> prev=root;
		while(p!=null&&p.value.compareTo(v)!=0)
		{
			prev=p;
			if(p.value.compareTo(v)>0) p=p.l;
			else p=p.r;
		}
		if(p!=null )
		{
			//System.out.println("Dla "+v+" ojciec:"+prev.value);
			return prev;
		}
		else System.out.println("Search: "+v+" nie ma");
		return null;
	}
	/**
	 * Zwraca liczbê wszystkich elementów w drzewie/
	 */
	public int size() {
		return size;
	}
	/**
	 * Zwraca aktualn¹ wysokoœæ drzewa.
	 */
	public int height() {
		height=0;
		return heightRecAux(root,1);
	}
	public int heightRecAux(Node<T> p,int count) {
		if(p!=null)
		{
			if(height<count) height=count;
			heightRecAux(p.l,count+1);
			heightRecAux(p.r,count+1);
		}
		return height;
	}
	/**
	 * Wypisz elementy drzewa metod¹ inorder. Ka¿dy element wypisz 
	 * tylukrotnie ile wynosi jego licznoœæ.
	 */
	public void printInorder() {
		if(root==null) return;
		System.out.print("InorderItr: ");
		Node<T> p=root;
		ArrayStack<Node<T>> stack=new ArrayStack<Node<T>>(1000);
		while(p!=null||!stack.isEmpty())
		{
			if(p!=null)
			{
				stack.push(p);
				p=p.l;
			}
			else
			{
				p=stack.pop();
				System.out.print(p.value+"("+p.count+")"+" "); 
				p=p.r;
			}
		}
		System.out.println();
	}
	public void printInorderRec(){System.out.print("InorderRec: "); printInorderRecAux(root); System.out.println();}
	public void printInorderRecAux(Node<T>p)
	{
		if(p!=null)
		{
			printInorderRecAux(p.l);
			System.out.print(p.value+"("+p.count+")"+" "); 
			printInorderRecAux(p.r);
		}
	}
	/**
	 * Usuwa poddrzewo zaczynaj¹ce siê w wêŸle o wartoœci v i zwraca je 
	 * jako nowe drzewo.
	 */
	public BST<T> cut(T v) {
		BST<T> t=new BST<T>();
		Node<T> p=search(v);
		cutRecAux(p,t);
		return t;
	}
	public void cutRecAux(Node<T> p,BST<T> t)
	{
		if(p!=null)
		{
			cutRecAux(p.l,t);
			cutRecAux(p.r,t);
			for(int i=1;i<=p.count;i++)
			{
				t.insertIter(p.value);
				deleteElem(p.value);
			}
		}
	}
	/**
	 * Wstawia wszystkie elementy drzewa tree.
	 */
	public void merge(BST<T> tree) {mergeRecAux(root);}
	public void mergeRecAux(Node<T> p)
	{
		if(p!=null)
		{
			mergeRecAux(p.l);
			mergeRecAux(p.r);
			for(int i=1;i<=p.count;i++)
			{
				insertIter(p.value);
			}
		}
	}
	public void display(){displayAux(root,1);}
	public void displayAux(Node<T> p,int h)
	{
		if(p!=null)
		{
			displayAux(p.r,h+1);
			for(int j=0; j<h; j++) System.out.print(' ');
			System.out.println(p.value);
			displayAux(p.l, h+1); 
		}
	}
	public class Node<E extends Comparable<E>> {
		Node<E> l,r;
		E value;
		int count;
		Node(E value) {
			this.value = value;
			count=1;
		}
	}
	class ArrayStack<E> {
		private int maxSize;
		private E[] Stack;
		private int top;
	    public ArrayStack(int maxSize) {
	    	this.maxSize=maxSize;
	    	this.Stack=(E[])new Object[maxSize];
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
	    public void push(E x) {
	    	if(!isFull())
	    	{
	    		top--;
	    		Stack[top]=x;
	    	}
	    }
	    public E top() {
	    	if(!isEmpty())
	    	{
	    		return Stack[top];
	    	}
	    	else return null;
	    }
	    public E pop() {
	    	if(!isEmpty())
	    	{
	    		top++;
	    		return Stack[top-1];
	    	}
	        return null;
	    } 
	    public void show(){
	    	if(!isEmpty())
	    	{
	    		for(int i=maxSize-1;i>=top;i--)
	    		{
	    			System.out.print(Stack[i]+" ");
	    		}
	    	}
	    }
	}
}

/*BST tree=new BST(9);
System.out.println("itr size: "+tree.size);
BST treeR=new BST(9);
System.out.println("rec size: "+treeR.size);
tree.insertIter(7);
tree.insertIter(7);
tree.insertIter(5);
tree.insertIter(6);
tree.insertIter(2);
tree.insertIter(4);
tree.insertIter(3);
tree.insertIter(3);
tree.insertIter(11);
tree.insertIter(10);
tree.insertIter(9);
tree.insertIter(2);
//System.out.println("itr size: "+tree.size);
//tree.printInorder();
//tree.printPreorder();
//tree.printPostorder();
//tree.printLevelorder();
System.out.println();
//rec
treeR.insertRec(7);
treeR.insertRec(7);
treeR.insertRec(5);
treeR.insertRec(6);
treeR.insertRec(2);
treeR.insertRec(4);
treeR.insertRec(3);
treeR.insertRec(3);
treeR.insertRec(11);
treeR.insertRec(10);
treeR.insertRec(9);
treeR.insertRec(2);
System.out.println("rec size: "+treeR.size);
//treeR.printInorder();
//treeR.printPreorder();
//treeR.printPostorder();
//treeR.printLevelorder();

System.out.println();
tree.delete(60);
treeR.delete(60);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();

System.out.println();//lewy syn
tree.delete(3);
treeR.delete(3);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();

System.out.println();//prawy syn
tree.delete(4);
treeR.delete(4);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();*/


/*System.out.println();//jeden w srodku
tree.deleteElem(7);
treeR.deleteElem(7);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();*/

/*	System.out.println();//dwoje synow
tree.delete(5);
treeR.delete(5);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();

System.out.println();//root
tree.delete(9);
treeR.delete(9);
System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();


BST tree2=new BST(9);//jeden element i null
System.out.println("tree2 size: "+tree2.size);
tree2.printInorder();
tree2.printPreorder();
tree2.printPostorder();
tree2.printLevelorder();
tree2.delete(9);
tree2.printInorder();
tree2.printPreorder();
tree2.printPostorder();
tree2.printLevelorder();*/

/*BST tree=new BST();
System.out.println("itr size: "+tree.size);
BST treeR=new BST();
System.out.println("rec size: "+treeR.size);
tree.insertIter(20);
tree.insertIter(22);
tree.insertIter(21);
tree.insertIter(8);
tree.insertIter(4);
tree.insertIter(12);
tree.insertIter(10);
tree.insertIter(14);
tree.insertIter(20);
tree.insertIter(21);

treeR.insertRec(20);
treeR.insertRec(22);
treeR.insertRec(21);
treeR.insertRec(8);
treeR.insertRec(4);
treeR.insertRec(12);
treeR.insertRec(10);
treeR.insertRec(14);
treeR.insertRec(14);
treeR.insertRec(21);

System.out.println("itr size: "+tree.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();
System.out.println("rec size: "+treeR.size);
treeR.printInorder();
treeR.printPreorder();
treeR.printPostorder();
treeR.printLevelorder();*/

/*	System.out.println("tree s:"+tree.successor(12));
System.out.println("treeR s:"+treeR.successor(12));
System.out.println("tree s:"+tree.successor(4));
System.out.println("treeR s:"+treeR.successor(4));
System.out.println("tree s:"+tree.successor(10));
System.out.println("treeR s:"+treeR.successor(10));
System.out.println("tree s:"+tree.successor(8));
System.out.println("treeR s:"+treeR.successor(8));
System.out.println("tree s:"+tree.successor(14));
System.out.println("treeR s:"+treeR.successor(14));
System.out.println("tree s:"+tree.successor(20));
System.out.println("treeR s:"+treeR.successor(20));
System.out.println("tree s:"+tree.successor(21));
System.out.println("treeR s:"+treeR.successor(21));
System.out.println("tree s:"+tree.successor(22));
System.out.println("treeR s:"+treeR.successor(22));
System.out.println();
System.out.println("rec size: "+treeR.size);*/

/*	System.out.println("tree s:"+tree.predecessor(12));
System.out.println("treeR s:"+treeR.predecessor(12));
System.out.println("tree s:"+tree.predecessor(4));
System.out.println("treeR s:"+treeR.predecessor(4));
System.out.println("tree s:"+tree.predecessor(10));
System.out.println("treeR s:"+treeR.predecessor(10));
System.out.println("tree s:"+tree.predecessor(8));
System.out.println("treeR s:"+treeR.predecessor(8));
System.out.println("tree s:"+tree.predecessor(14));
System.out.println("treeR s:"+treeR.predecessor(14));
System.out.println("tree s:"+tree.predecessor(20));
System.out.println("treeR s:"+treeR.predecessor(20));
System.out.println("tree s:"+tree.predecessor(21));
System.out.println("treeR s:"+treeR.predecessor(21));
System.out.println("tree s:"+tree.predecessor(22));
System.out.println("treeR s:"+treeR.predecessor(22));
System.out.println();
System.out.println("rec size: "+treeR.size);
*/
