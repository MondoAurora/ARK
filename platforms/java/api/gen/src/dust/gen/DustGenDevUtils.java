package dust.gen;

import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;

public interface DustGenDevUtils {
	public class DevTools {
		public static void logMemUsage() {
			MemoryMXBean mem = ManagementFactory.getMemoryMXBean();
			DustGenLog.log("Memory usage - heap:", mem.getHeapMemoryUsage(), "non heap:", mem.getNonHeapMemoryUsage());
		}
	}

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
		boolean showMem = false;
		
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
		
		public void setShowMem(boolean showMem) {
			this.showMem = showMem;
		}

		public boolean step() {
			boolean ret = false;
			++totalCount;
			++lastCount;
			long t = System.currentTimeMillis();
			if ( t > next ) {
				next = t + interval;
				if ( showMem ) {
					DustGenDevUtils.DevTools.logMemUsage();
				}
				log();
				lastCount = 0;
				ret = true;
			}
			return ret;
		}

		@Override
		public String toString() {
			return DustGenUtils
					.sbAppend(null, " ", false, super.toString(), "Total count:", totalCount, "Since last:", lastCount)
					.toString();
		}
	}
}
