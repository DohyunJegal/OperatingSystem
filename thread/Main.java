import java.io.*;
import java.lang.*;
import java.util.*;

class Sum {
    private int sum;
    public int getSum() { return sum; }
    public void setSum(int sum) { this.sum= sum; }
}

class Summation implements Runnable {	// Java 쓰레드 생성
    private int upper;
    private Sum sumValue;
	
    public Summation(int upper, Sum sumValue) {
        this.upper= upper;
        this.sumValue= sumValue;
    }
    public void run() {	// 인터페이스 Runnable을 구현한 클래스에서 run() 정의
        int sum = 0;
        for (int i= 0; i<= upper; i++) sum += i;
        sumValue.setSum(sum);
    }
}

public class Main
{
    public static void main(String[] args) {
        if (args.length> 0) {
            if (Integer.parseInt(args[0]) < 0)
                System.err.println(args[0] + " must be >= 0.");
            else {
                Sum sumObject= new Sum();
                int upper = Integer.parseInt(args[0]);
                Thread thrd= new Thread(new Summation(upper, sumObject));	// 새로운 쓰레드 생성
                thrd.start();	// 쓰레드 시작
				
                try {
                    thrd.join();	// 지정 쓰레드 종료시 까지 대기
                    System.out.println("The sum of " + upper + " is "
                            + sumObject.getSum());
                } catch (InterruptedException ie) {}
            }
        }
        else
            System.err.println("Usage: Summation <integer value>");
    }
}