package dust.gen;

import java.io.File;
import java.io.PrintStream;

public class DustGenLog implements DustGenConsts {

    static PrintStream psLog = System.out;
    static DustEventLevel logLevel = DustEventLevel.INFO;

    public static synchronized void log(DustEventLevel lvl, Object... obs) {
        if ( 0 < lvl.compareTo(logLevel) ) {
            return;
        }
        
        boolean first = true;

        for (Object o : obs) {
            String s = (null == o) ? "" : o.toString();

            if (first && !s.trim().isEmpty()) {
                first = false;
                psLog.print(DustGenUtils.strTimestamp());
                psLog.print(" ");
                psLog.print(lvl);
                psLog.print(" ");
            }
            psLog.print(s);
            psLog.print(" ");
        }

        if (!first) {
            psLog.println();
            psLog.flush();
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
        
        psLog = new PrintStream(fName + "_" + DustGenUtils.strTimestamp() + ".log");
    }
}
