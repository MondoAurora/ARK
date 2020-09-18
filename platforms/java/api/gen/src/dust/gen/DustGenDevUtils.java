package dust.gen;

public interface DustGenDevUtils {
    public class DevTimer {
        String header;
        long start;

        public DevTimer(String header) {
            this.header = header;
            this.start = System.currentTimeMillis();
            DustGenLog.log(header, "starting...");
        }

        @Override
        public String toString() {
            return header + " time: " + ((double) System.currentTimeMillis() - start) / 1000 + " sec.";
        }

        public void log() {
            DustGenLog.log(this);
        }
    }

    public class DevMonitor {
        long interval;
        long next;

        long totalCount;
        long lastCount;

        public DevMonitor(long interval) {
            this.interval = interval;
            totalCount = lastCount = 0;
            next = System.currentTimeMillis() + interval;
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

        public void log() {
            DustGenLog.log("Total count:", totalCount, "since last step:", lastCount);
        }
    }
}
