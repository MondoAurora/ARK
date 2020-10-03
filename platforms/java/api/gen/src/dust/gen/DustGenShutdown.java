package dust.gen;

import java.lang.ref.WeakReference;
import java.util.Stack;

import dust.gen.DustGenConsts.DustEventLevel;

public class DustGenShutdown {
	public interface ShutdownAware {
		void shutdown() throws Exception;
	}

	private static Stack<WeakReference<ShutdownAware>> shutdownStack;

	private static Thread shutdownProcess = new Thread() {
		@Override
		public synchronized void run() {
			while (!shutdownStack.isEmpty()) {
				ShutdownAware sa = shutdownStack.pop().get();
				if ( null != sa ) {
					try {
						DustGenLog.log(DustEventLevel.TRACE, "Shutting down", sa);
						sa.shutdown();
						DustGenLog.log(DustEventLevel.INFO, "Shutdown OK.");
					} catch (Throwable ex) {
						DustGenLog.log(DustEventLevel.ERROR, "Failed to stop", sa, ex);
					}
				}
			}
		}
	};

	public static synchronized int indexOf(ShutdownAware sa) {
		int ret = -1;
		if ( null != shutdownStack ) {
			for (int i = shutdownStack.size(); i-- > 0;) {
				WeakReference<ShutdownAware> wr = shutdownStack.get(i);
				ShutdownAware s = wr.get();

				if ( s == sa ) {
					ret = i;
				} else if ( null == s ) {
					shutdownStack.remove(i);
				}
			}
		}

		return ret;
	};

	public static synchronized boolean remove(ShutdownAware sa) {
		int idx = indexOf(sa);
		if ( -1 != idx ) {
			shutdownStack.remove(idx);
			return true;
		}
		return false;
	};

	public static synchronized boolean register(ShutdownAware sa) {
		if ( null == shutdownStack ) {
			shutdownStack = new Stack<>();
			Runtime.getRuntime().addShutdownHook(shutdownProcess);
		} else if ( -1 != indexOf(sa) ) {
			return false;
		}

		shutdownStack.push(new WeakReference<ShutdownAware>(sa));
		return true;
	}

}
