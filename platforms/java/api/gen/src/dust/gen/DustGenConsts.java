package dust.gen;

public interface DustGenConsts {
    enum DustResultType {
        NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ;
    };

    enum DustAgentAction {
        INIT, BEGIN, PROCESS, END, RELEASE
    };

    enum DustDialogCmd {
        CHK, GET, SET, ADD, DEL
    };

    public interface DustGenAgent {
        DustResultType agentAction(DustAgentAction action) throws Exception;
    }

    final long KEY_APPEND = -1;

    enum DustEventLevel {
        CRITICAL, ERROR, WARNING, INFO, TRACE, DEBUG
    };

    public class DustException extends RuntimeException {
        private static final long serialVersionUID = 1L;

        DustException(Throwable src) {
            super(src);
        }

        public static <FakeRet> FakeRet throwException(Throwable src, Object... params) {
            DustGenLog.log(DustEventLevel.CRITICAL, params);
            DustException e = (src instanceof DustException) ? (DustException) src : new DustException(src);
            throw e;
        }
    }

    public interface DustHasDefault<T> {
        T getDefault();
    }

    public interface DustCreator<T> {
        T create();
    }

    public interface DustEntity {
        String getGlobalId();
        public String getId();
    }
}
