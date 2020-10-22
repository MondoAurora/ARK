package dust.gen;

import java.io.File;
import java.io.FileFilter;
import java.io.FilenameFilter;
import java.util.regex.Pattern;

public abstract class DustGenFileFilter implements FilenameFilter, FileFilter, DustGenConsts {

	protected abstract boolean check(String name);

	@Override
	public boolean accept(File dir, String name) {
		return check(name);
	}

	@Override
	public boolean accept(File pathname) {
		return check(pathname.getName());
	}

	public static class Negate extends DustGenFileFilter {
		final DustGenFileFilter target;

		public Negate(DustGenFileFilter target_) {
			this.target = target_;
		}

		@Override
		protected boolean check(String name) {
			return !target.check(name);
		}
	}

	public static class Combined extends DustGenFileFilter {
		boolean any;
		final DustGenFileFilter[] members;

		public Combined(boolean any_, DustGenFileFilter... members_) {
			this.any = any_;
			this.members = members_;
		}

		@Override
		protected boolean check(String name) {
			for (DustGenFileFilter ff : members) {
				if ( ff.check(name) ) {
					if ( any ) {
						return true;
					}
				} else {
					if ( !any ) {
						return false;
					}
				}
			}

			return !any;
		}
	}

	public static class Regex extends DustGenFileFilter {
		private final Pattern pattern;

		public Regex(String regexp, int regexFlags) {
			this.pattern = Pattern.compile(regexp, regexFlags);
		}

		public Regex(String regexp) {
			this(regexp, 0);
		}

		@Override
		protected boolean check(String name) {
			return pattern.matcher(name).matches();
		}
	};

	public static DustGenFileFilter.Regex getEndFilter(String ext, boolean ignoreCase) {
		return new DustGenFileFilter.Regex(".*" + ext + "$", ignoreCase ? Pattern.CASE_INSENSITIVE : 0);
	}
}
