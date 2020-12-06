//Natalia Durlik 
import java.util.Scanner;
public class Source {
	public static Scanner in=new Scanner(System.in);
  public static void main(String[] args) {
  	int k=in.nextInt();
  	for(int z=0;z<k;z++)
  	{
  		int N=in.nextInt();
  		int P=in.nextInt();
  		MaxHeap heap=new MaxHeap(N,P);
  		String order="";
  		while(!order.equals("s"))
  		{
  			order=in.next();
  			if(order.equals("i"))
  			{
  				int insK=in.nextInt();
  				for(int i=0;i<insK;i++)
  				{
  					int x=in.nextInt();
  					heap.insert(x);
  				}
  			}
  			else if(order.equals("g"))
  			{
  				int getK=in.nextInt();
  				int[] elems=heap.getMax(getK);
  				if(elems[1]!=-1)
  				{
  					System.out.println(elems[0]+" "+elems[1]);
  				}
  				else System.out.println("0 0");
  			}
  			else if(order.equals("s"))
  			{
  				heap.heapSort();
  			}
  		}
  	}
  }
}
class MaxHeap {
	Node[] arr;
	int maxArr;//N
	int maxSize;//P
	int size;
	int totalSize;
	BST tree;
	public MaxHeap(int maxArr,int maxSize) {
		this.maxArr=maxArr;
		this.maxSize=maxSize;
		arr=new Node[maxArr];
		size=0;
		totalSize=0;
		tree=new BST();
	}
	public void insert(int v) {//O(log n)
		Node tmp=tree.search(v);
		if(tmp==null)//nie ma jeszcze takiej liczby w kolejce
		{
			if(!isFull()&&totalSize<maxSize)
			{
				arr[size]=new Node(v,1,size);//standarowe wstawienie do kopca 
				tree.insertIter(arr[size]);//wstawienie nowego noda do drzewa
				upheap(size);
				size++;
				totalSize++;
			}
		}
		else
			if(totalSize<maxSize) 
			{
				tmp.count++;
				totalSize++;
				upheap(tmp.idx);
			}
	}
	public int[] getMax(int k) {//O(log n)
		if(size>0&&k>0)
		{
			Node max=arr[0];
			if(max.count<=k)//usuwamy calego Noda
			{
				totalSize-=max.count;
				tree.delete(max);
				arr[0]=arr[size-1];
				arr[0].idx=0;
				size--;//bo size to rozne elementy
				downheap(0);
				return new int[] {max.value,max.count};//{wartosc,ilosc}
			}
			else 
			{
				arr[0].count-=k;
				downheap(0);
				totalSize-=k;
				return new int[] {max.value,k};
			}
		}
		return new int[] {-1,-1};
	}
	private void upheap(int idx) {
		int i=(idx-1)/2;//przodek
		Node tmp=arr[idx];
		while(idx>0&&
				(arr[i].count<tmp.count||
				(arr[i].count==tmp.count&&arr[i].value<tmp.value)))//kolejka jako liczba elementow
		{
			arr[idx]=arr[i];
			arr[idx].idx=idx;
			idx=i;
			i=(i-1)/2;
		}
		arr[idx]=tmp;
		arr[idx].idx=idx;
	}
	private void downheap(int t) {
		int j; 
		Node tmp=arr[t];
		while(t<size/2)
		{
			j=2*t+1;//lewy potomek
			if(j<size-1&&
				(arr[j].count<arr[j+1].count||
				(arr[j].count==arr[j+1].count&&arr[j].value<arr[j+1].value))) j++;
			if(tmp.count>arr[j].count||
				(tmp.count==arr[j].count&&tmp.value>arr[j].value)) break;
			arr[t]=arr[j];
			arr[t].idx=t;
			t=j;
		}
		arr[t]=tmp;
		arr[t].idx=t;
	}
	public void heapSort() {
		if(size>0)
		{
			while(size>0)
			{
				System.out.print(arr[0].value+" "+arr[0].count+" ");
				Node tmp = arr[0];
				arr[0]=arr[size-1];
			//	arr[0].idx=0;
				arr[size-1]=tmp;
			//	arr[size-1].idx=size-1;
				size--;
				downheap(0);
			}
			System.out.println();
		}
		else System.out.println("0 0");
	}
	public void showArr() {
		System.out.print("Heap arr:");
		for(int i=0;i<size;i++)
		{
			System.out.print(" "+arr[i].value+"("+arr[i].count+")");
		}
		System.out.println();
	}
	private boolean isFull() {
		if(size<maxArr) return false;
		return true;
	}
}
class BST {
	Node root;
	int size;
	public BST() {size=0;}
	public BST(int value) {
		root=new Node(value);
		size=1;
	}
	public void insertIter(Node v) {//wstawiamy Noda wzgledem value
		size++;
		if(root!=null)
		{
			int val=v.value;//pomocnicze tylko
			Node p=root;
			Node prev=root;
			while(p!=null&&p.value!=val)
			{
				prev=p;
				if(p.value>val) p=p.l;
				else p=p.r;
			}
			if(prev.value>val) prev.l=v;
			else prev.r=v;
		}
		else root=v;
	}
	public Node parent(int v)
	{
		if(root.value==v) 
		{
			return root;
		}
		Node p=root;
		Node prev=root;
		while(p!=null&&p.value!=v)
		{
			prev=p;
			if(p.value>v) p=p.l;
			else p=p.r;
		}
		if(p!=null ){return prev;}
		return null;
	}
	public Node search(int v) {
		Node p=root;
		while(p!=null&&p.value!=v)
		{
			if(p.value>v) p=p.l;
			else p=p.r;
		}
		//if(p!=null ) {}//System.out.println("Search: "+v+" "+p.value);
		//else {}//System.out.println("Search: "+v+" nie ma");
		return p;
	}
	public void delete(Node v)
	{
		int nVal=v.value;
		if(root.value==nVal)
		{
			size--;
			if(root.l==null&&root.r==null) root=null;
			else if(root.l!=null&&root.r==null) root=root.l;
			else if(root.l==null&&root.r!=null) root=root.r;
			else //root.l!=null&&root.r!=null
			{
				Node rs=root.r;
				if(rs.l==null)
				{
					root.value=rs.value;
					root.r=root.r.r;
				}
				else
				{
					Node fs=rs;
					while(rs.l!=null) 
					{
						fs=rs;
						rs=rs.l;
					}
					root.value=rs.value;
					fs.l=rs.r;
				}
			}
			return;
		}
		Node q=parent(nVal);//na poczatku root.value==v wiec ma rodzica
		if(q==null) return;//brak
		size--;
		boolean left=true;
		Node p=q.l;
		if(q.r!=null&&q.r.value==nVal) 
		{
			p=q.r;
			left=false;
		}
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
			Node s=p.r;
			if(s.l==null)
			{
				p.value=s.value;
				p.r=p.r.r;
			}
			else
			{
				Node f=s;
				while(s.l!=null)
				{
					f=s;
					s=s.l;
				}
				p.value=s.value;
				f.l=s.r;
			}
		}
	}
}
class Node {
	public int value;
	public int count;
	public int idx;
	public Node l;
	public Node r;
	public Node(int value) {this.value=value;}//FIXME
	public Node(int value,int count,int idx)
	{
		this.value=value;
		this.count=count;
		this.idx=idx;
	}
}




/*
BST tree=new BST();
MaxHeap heap=new MaxHeap(10,6);
heap.insert(5, tree);
//heap.showArr();
heap.insert(5, tree);
heap.insert(5, tree);
heap.insert(5, tree);
heap.insert(5, tree);
heap.insert(5, tree);
heap.insert(6, tree);
heap.insert(30, tree);
heap.insert(15, tree);
heap.insert(16, tree);
heap.insert(15, tree);
heap.insert(16, tree);
heap.insert(15, tree);
//	heap.showArr();
heap.insert(16, tree);
//heap.showArr();
heap.insert(31, tree);
heap.showArr();

System.out.println(heap.getMax(3,tree)[0]);
heap.showArr();
/*System.out.println(heap.getMax(50,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(50,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(50,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(50,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(50,tree)[0]);
heap.showArr();*/

/*System.out.println(heap.getMax(1,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(1,tree)[0]);
heap.showArr();
System.out.println(heap.getMax(1,tree)[0]);
heap.showArr();*/

/*


2
5 15
g 2
0 0
i 2 1 1
g 1
1 1
i 3 2 3 4
g 2
4 1
i 7 4 4 4 4 4 1 3
g 3
4 3
i 9 2 6 1 6 7 7 7 7 2
g 2
2 2
s
1 3 6 2 4 2 3 2 2 1 8 15
i 10 1 2 3 4 5 6 7 8 9 10
g 2
8 1
g 1
7 1
g 5
6 1
i 10 1 1 1 1 1 1 1 1 4 4
g 3
1 3
i 15 1 1 1 1 1 1 1 1 1 1 1 1 3 3 3
g 30
1 9
g 2
4 2
i 11 3 3 3 5 5 5 5 10 10 2 1
s
5 5 3 4 10 2 2 2 4 1 1 1 
*/