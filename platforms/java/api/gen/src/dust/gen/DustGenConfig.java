package dust.gen;

import java.util.Map;

public class DustGenConfig {
	Map<String, Object> map;
	
	public DustGenConfig(Map<String, Object> src) {
		this.map = src;
	}

	public Map<String, Object> getMap() {
		return map;
	}
	
	public String getString(String... path) {
		return get(path);
	}

	public <RetType> RetType getWithDefault(RetType defVal, String... path) {
		RetType r = get(path);
		return (null == r) ? defVal : r;
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public <RetType> RetType get(String... path) {
		Object ret = map;

		for (String key : path) {
			if ( null == ret ) {
				return null;
			}

			ret = ((Map) ret).get(key);
		}

		return (RetType) ret;
	}
}
