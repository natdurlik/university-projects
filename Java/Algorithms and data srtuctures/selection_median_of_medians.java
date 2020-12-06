//Natalia Durlik
import java.util.Scanner;

public class Source{
	public static int[]arr;
	public static int firstx;
	public static Scanner in=new Scanner(System.in);
	public static void main(String[] args)
	{
		int k=in.nextInt();
    	for(int z=0;z<k;z++)
    	{
    		int n=in.nextInt();
			arr=new int[n];
    		for(int i=0;i<n;i++)
    		{
    			arr[i]=in.nextInt();
    		}
    		int m=in.nextInt();
    		for(int i=0;i<m;i++)
    		{
    			int kthSmall=in.nextInt();
    			if(kthSmall<=0||kthSmall>arr.length) System.out.println(kthSmall+" brak");
    			else System.out.println(kthSmall+" "+medianOfMedians5(0,arr.length-1,kthSmall));
    		}
    	}
	}
	static int medianOfMedians5(int l,int r,int k)//5 elements
	{
		int size=r-l+1;
		if(size<=30)
		{
			insertionSort(l,r);
			return arr[l+k-1];
		}
		int i;
		int mediansSize=0;
		for(i=l;i+4<r+1;i+=5)
		{
			swap(mediansSize+l,median(i,i+4));//dodajemy l bo 
			mediansSize++;
		}
		if(i<r+1) 
		{
			swap(mediansSize+l,median(i,r));
			mediansSize++;
		}
		int median=medianOfMedians5(l,(mediansSize-1)+l,mediansSize/2+1);//(a,l,r,k)
		int pivot=partitionMedian(l,r,median);
		if(l+k<=firstx) return medianOfMedians5(l,firstx-1,k);//if (k<=|S1| )
		if(l+k-1<=pivot) return median;//if (k<=|S1|+|S2|)
		return medianOfMedians5(pivot+1,r,l+k-pivot-1);// (S3,k-|S1|-|S2|);
	}
	static int partitionMedian(int l,int r,int pivot)
	{
		for(int z=l;z<r;z++)
		{
			if(arr[z]==pivot)//by przestawic pivota na r
			{
				swap(z,r);
				break;
			}
		}
		int x=arr[r];
		int xes=1;
		firstx=-1;
		int j=l-1;
		for(int i=l;i<r;i++)//jak w quickSort
		{
			if(arr[i]<=x)
			{
				if(arr[i]==x) xes++;
				j++;
				swap(i,j);
			}
		}
		j++;
		swap(j,r);
		if(xes>1) 
		{
			int idx=j-1;
			for(int i=j-1;i>=0&&xes>1;i--)
			{
				if(arr[i]==x)
				{
					swap(i,idx);
					idx--;
					xes--;
				}
			}
			firstx=idx+1;
		}
		else firstx=j;//pivot stoi na j i sie nie powtarza 
		return j;
	}
	static void swap(int i, int j) 
	{
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	static int median(int l,int r)
	{
		insertionSort(l,r);
		return l+(r-l+1)/2;
	}
	static void insertionSort(int l,int r)//sorts [l-r]
	{
		for(int i=l+1;i<r+1;i++)
		{
			int x=arr[i];
			int j=i-1;
			while(j>=l&&arr[j]>x)
			{
				arr[j+1]=arr[j];	
				j--;
			}
			arr[j+1]=x;
		}
	}
}


/* testy 
 z bacy:
 3
5
1 2 3 4 5
3
1
1 1
2
2 2
3
3 3
5
5 3 4 4 3
5
2
2 3
5
5 5
1
1 3
3
3 4
4
4 4
10
1 1 1 1 1 1 1 1 1 1
5
1
1 1
10
10 1
0
0 brak
-1
-1 brak
11
11 brak


 		int size=100;
		arr=new int[size];
		
		Random rnd = new Random();
		for(int i=0;i<size;i++) arr[i] = rnd.nextInt(10);
		
		int k=rnd.nextInt(size);
		
		System.out.println(Arrays.toString(arr));
		if(k<=0||k>arr.length) System.out.println("brak");
		else 
		{
			int kthEl=medianOfMedians5(0,arr.length-1,k);
			System.out.println(k+"-ty najmniejszy: "+kthEl);
			Arrays.sort(arr);
			if(kthEl==arr[k-1]) System.out.println("passed "+arr[k-1]+"="+kthEl);
			else System.out.println(arr[k-1]+"!="+kthEl);
		}
*/
