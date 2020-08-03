package dust.mod.jdbc;

import java.lang.ref.WeakReference;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

import dust.mod.DustUtils;

public class JdbcUtils implements JdbcComponents {

    public static final void dumpResultSet(ResultSet rs, String... colNames ) throws Exception {
        if ( null != colNames ) {
            colNames = getAllColumnNames(rs);
        }
        
        StringBuilder sb = null;
        for ( String col : colNames ) {
            sb = DustUtils.sbAppend(sb, "\t", true, col);
        }
        System.out.println(sb);
        
//        if ( ResultSet.TYPE_FORWARD_ONLY == rs.getType() ) {
//            DustUtils.log(DustEventLevel.INFO, "Skip dumping forward only resultset");
//            return;
//        }
        
        for ( boolean ok = optFirst(rs); ok; ok = rs.next() ) {
            sb = null;
            
            for ( String col : colNames ) {
                sb = DustUtils.sbAppend(sb, "\t", true, rs.getObject(col));
            }
            System.out.println(sb);
        }
    }

    public static boolean optFirst(ResultSet rs) throws Exception {
        if ( ResultSet.TYPE_FORWARD_ONLY != rs.getType() ) {
            return rs.first();
        } else { 
            if ( rs.isAfterLast() ) {
                throw new IllegalStateException("Already called optFirst on a ForwardOnly ResultSet!");
            } else {
                return rs.next();
            }
        }
    }

    public static String[] getAllColumnNames(ResultSet rs) throws Exception {
        String[] colNames;
        ResultSetMetaData rsmd = rs.getMetaData();
        int cc = rsmd.getColumnCount();
        colNames = new String[cc];
        for ( int i = 0; i < cc; ++i ) {
            colNames[i] = rsmd.getColumnName(i+1);
        }
        return colNames;
    }

    public static Map<String, Object> mapFromRS(ResultSet rsFrom, String... colNames) {
        Map<String, Object> ret = new TreeMap<String, Object>();
        
        if ( null != colNames ) {
            try {
                colNames = getAllColumnNames(rsFrom);
            } catch (Throwable e) {
                DustException.throwException(e);
            }
        }
        
        for ( String col : colNames ) {
            try {
                ret.put(col, rsFrom.getObject(col));
            } catch (Throwable e) {
                ret.put(col, e);
            }
        }
        
        return ret;
    }
    
    private static Set<WeakReference<Connection>> CONNECTIONS = new HashSet<>();

    static {
        Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                for (WeakReference<Connection> wrc : CONNECTIONS) {
                    Connection c = wrc.get();
                    if (null != c) {
                        try {
                            releaseConn(c, null);
                        } catch (Throwable e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        });
    }
    
    public static void addConn(Connection conn) {
        CONNECTIONS.add(new WeakReference<Connection>(conn));
    }

    public static void releaseConn(Connection conn, Throwable cause) throws Exception {
        if (null != conn) {
            if (!conn.isClosed()) {
                if (!conn.getAutoCommit()) {
                    if (null == cause) {
                        conn.commit();
                    } else {
                        conn.rollback();
                    }
                }
                conn.close();
                System.out.println("DB connection closed.");
            }
        }
    }
}
