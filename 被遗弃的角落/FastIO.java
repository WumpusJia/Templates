import java.io.*;
import java.util.*;
import java.math.*;

class Main{

	static class Reader{
		static BufferedReader reader;
		static StringTokenizer tokenizer;

		static void init(InputStream input){
			reader=new BufferedReader(new InputStreamReader(input));
			tokenizer= new StringTokenizer("");
		}

		static String next() throws IOException {
			String s;
			while(!tokenizer.hasMoreTokens()){
				if((s=reader.readLine())==null) return null;
				tokenizer = new StringTokenizer(s);
			}
			return tokenizer.nextToken();
		}

		static Integer nextInt() throws IOException {
			String s=next();
			if(s==null) return null;
			return Integer.parseInt(s);
		}

		static Double nextDouble() throws IOException {
			String s=next();
			if (s==null) return null;	
			return Double.parseDouble(s);
		}
	}

	public static void main(String[] args) throws IOException{
		//InputStream f=new FileInputStream("/home/alex/Desktop/test.txt");
		//Reader.init(f);
		Reader.init(System.in);
		BigDecimal R;
		int n;
		while(true){
			String s=Reader.next();
			if(s==null) break;
			R=new BigDecimal(s);
			R=R.stripTrailingZeros();
			n=Reader.nextInt();
			R=R.pow(n);
			String S=R.toPlainString();
			if(S.charAt(0)=='0') S=S.substring(1,S.length());
			System.out.println(S);	
		}
	}
}



