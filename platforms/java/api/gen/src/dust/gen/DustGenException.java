package dust.gen;

import dust.gen.DustGenConsts.DustEventLevel;

public class DustGenException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    DustGenException(Throwable src) {
        super(src);
    }

    public static <FakeRet> FakeRet throwException(Throwable src, Object... params) {
        DustGenLog.log(DustEventLevel.CRITICAL, params);
        DustGenException e = (src instanceof DustGenException) ? (DustGenException) src : new DustGenException(src);
        throw e;
    }
}