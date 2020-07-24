package dust.mod;

import java.util.HashMap;
import java.util.Map;

public class DustModule implements DustComponents {
	private Map<Long, Class<?>> moduleClasses = new HashMap<Long, Class<?>>();
	
	public Object createNative(Long typeId) {
		try {
			return moduleClasses.get(typeId).newInstance();
		} catch (Exception e) {
			DustException.throwException(e, typeId);
			return null;
		}
	}

	protected void registerClass(Long typeId, Class<?> c) {
		moduleClasses.put(typeId, c);
	}
}
