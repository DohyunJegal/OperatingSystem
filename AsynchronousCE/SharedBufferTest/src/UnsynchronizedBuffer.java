public class UnsynchronizedBuffer implements Buffer { // 공유하는 단일 정수 관리 클래스
    private int buffer = -1;

    public void set(int value) {	// Buffer의 set()을 구현 
        System.err.println(Thread.currentThread().getName() + " 저장한값: " + value);
        buffer = value;
    }

    public int get() {	// Buffer의 get()을 구현 
        System.err.println(Thread.currentThread().getName() + " 읽은값: " + buffer);
        return buffer;
    }
}

