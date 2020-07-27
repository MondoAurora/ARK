package dust.mod;

public class DustUtils implements DustComponents {
	public static boolean isEqual(Object o1, Object o2) {
		return ( null == o1 ) ? ( null == o2 ) : ( null != o2 ) && o1.equals(o2);
	}
	
}
