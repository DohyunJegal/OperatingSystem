public class UnsynchronizedBuffer implements Buffer {
    private int buffer = -1;

    public void set(int value) {
        System.err.println(Thread.currentThread().getName() + " 저장한값: " + value);
        buffer = value;
    }

    public int get() {
        System.err.println(Thread.currentThread().getName() + " 읽은값: " + buffer);
        return buffer;
    }
}