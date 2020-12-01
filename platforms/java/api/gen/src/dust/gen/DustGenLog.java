package dust.gen;

import java.io.File;
import java.io.PrintStream;
import java.util.HashSet;
import java.util.Set;

public class DustGenLog implements DustGenConsts {

    static PrintStream psLog = System.out;
    static DustEventLevel logLevel = DustEventLevel.INFO;
    
    static Set<LogListener> listeners = new HashSet<>();
    
    public static boolean setListener(LogListener l, boolean set) {
    	return (null == l) ? false : set ? listeners.add(l) : listeners.remove(l);
    }

    public static synchronized void log(DustEventLevel lvl, Object... obs) {
        if ( 0 < lvl.compareTo(logLevel) ) {
            return;
        }
        
        long ts = 0;
        StringBuilder sb = null;

        for (Object o : obs) {
            String s = DustGenUtils.toStringSafe(o);
            if ( null == s ) {
            	s = "";
            }

            if ((0 == ts) && !s.trim().isEmpty()) {
                ts = System.currentTimeMillis();
                psLog.print(DustGenUtils.strTimestamp(ts));
                psLog.print(" ");
                psLog.print(lvl);
                psLog.print(" ");
            }
            psLog.print(s);
            psLog.print(" ");
            
            sb = DustGenUtils.sbAppend(sb, " ", true, s);
        }

        if (0 != ts) {
            psLog.println();
            psLog.flush();
            
            for ( LogListener l : listeners ) {
            	try {
            		l.processLog(ts, lvl, sb.toString());
            	} catch (Throwable t) {
            		// nevermind...
            	}
            }
        }
    }

    public static void log(Object... obs) {
        log(DustEventLevel.INFO, obs);
    }

    public static void setLogLevel(DustEventLevel lvl) {
        logLevel = lvl;
        log(DustEventLevel.INFO, "LogLevel set to", lvl);
    }

    public static void setLogFile(String fName) throws Exception {
        if ( (null != psLog) && (psLog != System.out) ) {
            psLog.flush();
            psLog.close();
        }
        
        File f = new File(fName).getAbsoluteFile();
        File p = f.getParentFile();
        
        if (!p.exists() ) {
            p.mkdirs();
        }
        
        String fnameLog = fName + "_" + DustGenUtils.strTimestamp() + ".log";
				psLog = new PrintStream(fnameLog);
        
        System.out.println("Log file set to " + fnameLog);
        log(DustEventLevel.INFO, "Log file started", fnameLog);
    }
}
