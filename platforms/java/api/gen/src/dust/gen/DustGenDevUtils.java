package dust.gen;

public interface DustGenDevUtils {
    public class DevTimer {
        String name;
        long start;

        public DevTimer(String header) {
            this.name = header;
            this.start = System.currentTimeMillis();
            DustGenLog.log(header, "starting...");
        }

        @Override
        public String toString() {
            return name + " Elapsed: " + ((double) System.currentTimeMillis() - start) / 1000 + "(s)";
        }

        public void log() {
            DustGenLog.log(this);
        }
    }

    public class DevMonitor extends DevTimer {
        long interval;
        long next;

        long totalCount;
        long lastCount;

        public DevMonitor(long interval, String name) {
        	super(name);

        	this.interval = interval;
            totalCount = lastCount = 0;
            start = System.currentTimeMillis();
            next = start + interval;
        }

        public boolean step() {
            boolean ret = false;
            ++totalCount;
            ++lastCount;
            long t = System.currentTimeMillis();
            if (t > next) {
                next = t + interval;
                log();
                lastCount = 0;
                ret = true;
            }
            return ret;
        }

        @Override
        public String toString() {
        	return DustGenUtils.sbAppend(null, " ", false, super.toString(), "Total count:", totalCount, "Since last:", lastCount).toString();
        }
    }
}
