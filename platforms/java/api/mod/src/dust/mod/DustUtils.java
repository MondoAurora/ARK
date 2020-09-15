package dust.mod;

import java.util.HashMap;
import java.util.Map;

import dust.gen.DustGenUtils;

public class DustUtils extends DustGenUtils implements DustComponents {

    public static class TokenUtils {
        public final int typeText;
        public final int refNative;
        public final int refTag;

        public TokenUtils(DustToken typeText, DustToken refNative, DustToken refTag) {
            this.typeText = typeText.getEntity();
            this.refNative = refNative.getEntity();
            this.refTag = refTag.getEntity();
        }

        public void setTextMember(int entity, int refToken, int key, String str) {
            DustDialogTray tray = new DustDialogTray();

            tray.entity = null;
            tray.token = typeText;
            Integer eParam = Dust.access(DustDialogCmd.ADD, tray);

            tray.entity = eParam;
            tray.token = refNative;
            tray.key = typeText;
            tray.value = str;
            Dust.access(DustDialogCmd.SET, tray);

            tray.entity = entity;
            tray.token = refToken;
            tray.key = key;
            tray.value = eParam;
            Dust.access(DustDialogCmd.SET, tray);
        }

        public String getTextMember(int entity, int refToken, int key, String defValue) {
            String ret = defValue;

            DustDialogTray tray = new DustDialogTray();
            tray.entity = entity;
            tray.token = refToken;
            tray.key = key;
            Integer eParam = Dust.access(DustDialogCmd.GET, tray);

            if (null != eParam) {
                tray.entity = eParam;
                tray.token = refNative;
                tray.key = typeText;
                ret = Dust.access(DustDialogCmd.GET, tray);
            }

            return ret;
        }

        public Map<DustToken, String> getTextParams(Map<DustToken, String> map, int entity, DustToken... members) {
            if ( null == map ) {
                map = new HashMap<>();
            } else {
                map.clear();
            }
            
            for ( DustToken t : members ) {
                String s = getTextMember(entity, t.getEntity(), 0, null);
                if ( null != s ) {
                    map.put(t, s);
                }
            }
            
            return map;
        }

        public void setMemberMeta(DustToken member, DustToken valType, DustToken collType) {
            DustDialogTray t = new DustDialogTray();
            t.entity = member.getEntity();
            t.token = refTag;

            t.value = valType.getEntity();
            Dust.access(DustDialogCmd.ADD, t);
            t.value = collType.getEntity();
            Dust.access(DustDialogCmd.ADD, t);
        }
    }
}
