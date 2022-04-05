import java.io.*;
import java.lang.*;
import java.util.*;

class PrintThread extends Thread{	// Java 쓰레드 생성
    private int sleepTime;
    public PrintThread(String name) {
        super(name);
        sleepTime= (int) (Math.random( )* 3001);
    }
    public void run( ) {	// 클래스 Thread를 상속한 클래스의 run()
        try {
            System.out.println(getName( ) + " sleeps for " + sleepTime+ "msec");
            Thread.sleep(sleepTime); ;
        }
        catch (InterruptedException exception) {
            exception.printStackTrace( );
        }
    }
}

public class ThreadTest{
    public static void main(String[ ] args) {
        PrintThread thread1 = new PrintThread("Thread 1");	// 쓰레드 생성
        PrintThread thread2 = new PrintThread("Thread 2");
        PrintThread thread3 = new PrintThread("Thread 3");
        System.out.println("쓰레드 시작");
        thread1.start( );	// 쓰레드 시작
        thread2.start( );
        thread3.start( );
        System.out.println("전체 쓰레드 시작 완료");
    }
}