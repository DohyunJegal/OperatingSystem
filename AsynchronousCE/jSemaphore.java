import java.util.Random;
import java.util.concurrent.Semaphore;

class Log{
    public static void show(String strMessage) {
        System.out.println(Thread.currentThread().getName() + " : " + strMessage);
    }
}

class BoundedResource{
    private final Semaphore m_Semaphore; // 세마포어선언
    private final int m_nPermits;
    private final static Random m_Random= new Random(10000);

    public BoundedResource(int nCount) {
        this.m_Semaphore= new Semaphore(nCount); // 세마포어생성
        this.m_nPermits= nCount;
    }

    public void use( ) throws InterruptedException{
        m_Semaphore.acquire( ); // 세마포어리소스확보, P 연산
        try {
            doUse( );
        }
        finally {
            m_Semaphore.release( ); // 세마포어리소스해제, V 연산
        }
    }

    protected void doUse( ) throws InterruptedException{ // 세마포어가용값
        Log.show("Begin : 사용중인 Resource 개수= " + (m_nPermits-m_Semaphore.availablePermits( )));
        Thread.sleep(m_Random.nextInt(500));
        Log.show("End : 사용중인 Resource 개수= " + (m_nPermits-m_Semaphore.availablePermits( )));
    }
}

class UserThread extends Thread {
    private final static Random m_Random= new Random(10000);
    private final BoundedResource m_resource;
    public UserThread(BoundedResource resource) {
        m_resource= resource;
    }

    public void run( ) {
        try {
            while(true) {
                m_resource.use( );
                Thread.sleep(m_Random.nextInt(3000));
            }
        }
        catch(InterruptedException e) { }
    }
}

public class jSemaphore {
    public static void main(String[ ] argc) {
        System.out.println("Starting...");
        BoundedResource resource = new BoundedResource(3); // 3개의가용자원할당
        for(int i=0; i<10; i++) {
            new UserThread(resource).start( ); // 10개쓰레드생성
        }
    }
}
