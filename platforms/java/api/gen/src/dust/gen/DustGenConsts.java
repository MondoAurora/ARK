package dust.gen;

import java.util.EnumSet;

public interface DustGenConsts {
	String ENCODING_UTF8 = "UTF-8";
	String FORMAT_DATE_DEFAULT = "YYYYMMdd";
	String FORMAT_TIMESTAMP_DEFAULT = "YYYYMMdd_HHmmss_SSS";

	final long KEY_APPEND = -1;

	enum DustValType {
		INT, REAL, REF, RAW
	}

	enum DustCollType {
		ONE, ARR, SET, MAP
	}

	enum DustEventLevel {
		CRITICAL, ERROR, WARNING, INFO, TRACE, DEBUG
	};

	enum DustAgentAction {
		INIT, BEGIN, PROCESS, END, RELEASE
	};

	enum DustDialogCmd {
		CHK, GET, SET, ADD, DEL
	};

	enum DustResultType {
		NOTIMPLEMENTED, REJECT, ACCEPT_PASS, ACCEPT, ACCEPT_READ, READ;
		
		private static final EnumSet<DustResultType> RT_ACCEPT = EnumSet.of(ACCEPT_PASS, ACCEPT, ACCEPT_READ);
		private static final EnumSet<DustResultType> RT_READ = EnumSet.of(READ, ACCEPT_READ);
		private static final EnumSet<DustResultType> RT_REJECT = EnumSet.of(NOTIMPLEMENTED, REJECT);

		public boolean isAccept() {
			return RT_ACCEPT.contains(this);
		}

		public boolean isReadOn() {
			return RT_READ.contains(this);
		}

		public boolean isReject() {
			return RT_REJECT.contains(this);
		}
	};

	public interface DustEntity {
	}

	interface DustMemberDef {
		DustEntity getTypeEntity();

		DustEntity getDefEntity();

		DustCollType getCollType();

		DustValType getValType();
	}

	class DustEntityDelta {
		public DustDialogCmd cmd;

		public DustEntity target;
		public Object eKey;

		public DustEntity member;
		public Object value;
		public Object key;

		public DustEntityDelta(DustDialogCmd cmd, DustEntity target, Object eKey, DustEntity member, Object value,
				Object key) {
			this.cmd = cmd;
			this.target = target;
			this.eKey = eKey;
			this.member = member;
			this.value = value;
			this.key = key;
		}

		public void set(DustDialogCmd cmd, DustEntity target, Object eKey, DustEntity member, Object value, Object key) {
			this.cmd = cmd;
			this.target = target;
			this.eKey = eKey;
			this.member = member;
			this.value = value;
			this.key = key;
		}

		@Override
		public String toString() {
			StringBuilder sb = DustGenUtils.sbAppend(null, ",", true, target, cmd, member, value, key);
			return sb.toString();

		}
	}

	enum EntityBlock {
		Entity, Member
	}

	public class DustEntityContext {
		public EntityBlock block;

		public DustEntity entity;
		public Object entityId;

		public DustEntity member;

		public DustValType valType;
		public DustCollType collType;

		public Object value;
		public Object key;

		public DustEntityContext() {
		}

		public DustEntityContext(DustEntityContext src) {
			load(src);
		}

		public void load(DustEntityContext src) {
			this.block = src.block;
			this.entity = src.entity;
			this.member = src.member;
			this.valType = src.valType;
			this.collType = src.collType;
			this.value = src.value;
			this.key = src.key;
			this.entityId = src.entityId;
		}

		public void reset() {
			this.block = null;
			this.entity = null;
			this.member = null;
			this.valType = null;
			this.collType = null;
			this.value = null;
			this.key = null;
			this.entityId = null;
		}

		@Override
		public String toString() {
			StringBuilder sb = DustGenUtils.sbAppend(null, ",", true, block, entity, entityId, member, valType, collType,
					value, key);
			return sb.toString();
		}
	}

	public interface DustAgent {
		DustResultType agentAction(DustAgentAction action) throws Exception;
	}

	public interface DustDeltaListener {
		void processDelta(DustEntityDelta delta) throws Exception;
	}
	
	interface LogListener {
		void processLog(long timestamp, DustEventLevel level, String str);
	}
}
