package dust.mod;

import java.util.HashMap;
import java.util.Map;

public class DustModule implements DustComponents {
	private Map<Integer, Class<?>> moduleClasses = new HashMap<Integer, Class<?>>();
	
	public Object createNative(int typeId) {
		try {
			return moduleClasses.get(typeId).newInstance();
		} catch (Exception e) {
			DustException.throwException(e, typeId);
			return null;
		}
	}

	protected void registerClass(int typeId, Class<?> c) {
		moduleClasses.put(typeId, c);
	}
}
