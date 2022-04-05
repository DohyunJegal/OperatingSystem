import java.util.Vector;

class Producer extends Thread {
    static final int MAXQUEUE = 5;
    private Vector messages = new Vector();

    public void run() {	// Java의 쓰레드 생성을 위해 Thread를 상속받고 run() 생성
        try {
            while (true) {
                putMessage();
                sleep(1000);
            }
        } catch (InterruptedException e) {
        }
    }

    private synchronized void putMessage() throws InterruptedException {	// synchronized 카워드로 해당 객체의 상호 배제 강제
        while (messages.size() == MAXQUEUE) {
            wait();	// 호출 쓰레드 모니터에 대한 잠금 반환 후 대기 집합에 자신 추가, 쓰레드 상태는 대기로 변경
        }
		
        messages.addElement(new java.util.Date().toString());
        System.out.println("put message");
        notify();	// 대기 집합에서 하나의 쓰레드를 진입 집합으로 이동
    }

    public synchronized String getMessage() throws InterruptedException {
        notify();
        while (messages.size() == 0) {
            wait();
        }
		
        String message = (String) messages.firstElement();
        messages.removeElement(message);
		
        return message;
    }
}