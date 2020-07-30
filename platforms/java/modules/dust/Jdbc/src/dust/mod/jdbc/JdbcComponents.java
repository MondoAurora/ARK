package dust.mod.jdbc;

import dust.mod.DustComponents;

public interface JdbcComponents  extends DustComponents {
    
    String JDBC_TABLE_NAME = "TABLE_NAME";
    String JDBC_TABLE = "TABLE";
    String JDBC_TYPE_NAME = "TYPE_NAME";
    String JDBC_PKTABLE_NAME = "PKTABLE_NAME";
    String JDBC_FKCOLUMN_NAME = "FKCOLUMN_NAME";
    String JDBC_COLUMN_NAME = "COLUMN_NAME";

    
    enum DustJdbcTypes {
        JdbcConnector, JdbcDataType, JdbcTable, JdbcColumn, JdbcRecord
    };
    
    enum DustJdbcAtts {
        RecordContent, RecordLastUpdate, RecordOwner
    }
    
    enum DustJdbcLinks {
        DataTypeToDustType, ConnectorDataTypes, ColumnType
    }
    
    enum DustJdbcServices {
        JdbcConnector
    };


}
