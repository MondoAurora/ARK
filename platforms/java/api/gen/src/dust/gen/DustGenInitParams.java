package dust.gen;

import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DustGenInitParams<T extends Enum<T>> implements DustGenConsts {
	Map<T, String> pv = new HashMap<>();

	public DustGenInitParams(String[] args, Class<T> tc) {
		Pattern p = Pattern.compile("-(\\w*)=(\\S*)");
		for (String arg : args ) {
			Matcher m = p.matcher(arg);
			
			if (m.matches() ) {
				String k = m.group(1);
				T pk = DustGenUtils.fromString(k, tc);
				if ( null != pk ) {
					pv.put(pk, m.group(2));
				}
			}
		}
	}

	@SuppressWarnings("unchecked")
	public String getString(T param) {
		String v = pv.get(param);
		return (null == v) ? ((DustGenUtils.HasDefault<String>)param).getDefault() : v;
	}

	public int getInt(T param) {
		return Integer.parseInt(getString(param));
	}
}