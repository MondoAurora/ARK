CREATE DATABASE  IF NOT EXISTS `ark01` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `ark01`;
-- MySQL dump 10.13  Distrib 8.0.18, for Win64 (x86_64)
--
-- Host: localhost    Database: ark01
-- ------------------------------------------------------
-- Server version	8.0.18

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `mind_core_binary`
--

DROP TABLE IF EXISTS `mind_core_binary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_core_binary` (
  `EntityId` int(11) NOT NULL,
  `BinaryMedium` mediumblob,
  `BinaryLong` longblob,
  PRIMARY KEY (`EntityId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_core_binary`
--

LOCK TABLES `mind_core_binary` WRITE;
/*!40000 ALTER TABLE `mind_core_binary` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_core_binary` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_core_data`
--

DROP TABLE IF EXISTS `mind_core_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_core_data` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `Key` int(10) unsigned zerofill NOT NULL,
  `ValInteger` int(11) DEFAULT NULL,
  `ValReal` double DEFAULT NULL,
  `ValRef` int(11) DEFAULT NULL,
  PRIMARY KEY (`EntityId`,`MemberId`,`Key`),
  KEY `idx_mind_core_data_MemberId` (`MemberId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_core_data`
--

LOCK TABLES `mind_core_data` WRITE;
/*!40000 ALTER TABLE `mind_core_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_core_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_core_entity`
--

DROP TABLE IF EXISTS `mind_core_entity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_core_entity` (
  `StoreId` int(11) NOT NULL AUTO_INCREMENT COMMENT 'External ID, known by other components. Represents the current state of the entity',
  `PrimaryType` int(11) NOT NULL,
  `InitialId` int(11) NOT NULL,
  `CommitId` int(11) DEFAULT NULL COMMENT 'If the entity is versioned',
  `State` int(11) DEFAULT NULL COMMENT 'Null means "OK"',
  `Idx01` int(11) DEFAULT NULL,
  `Idx02` int(11) DEFAULT NULL,
  `Idx03` int(11) DEFAULT NULL,
  PRIMARY KEY (`StoreId`),
  UNIQUE KEY `StoreID_UNIQUE` (`StoreId`) /*!80000 INVISIBLE */,
  KEY `PRIMARY_TYPE` (`PrimaryType`) /*!80000 INVISIBLE */,
  KEY `INITIAL_ID` (`InitialId`,`CommitId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_core_entity`
--

LOCK TABLES `mind_core_entity` WRITE;
/*!40000 ALTER TABLE `mind_core_entity` DISABLE KEYS */;
INSERT INTO `mind_core_entity` VALUES (1,1,42,1,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `mind_core_entity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_core_text`
--

DROP TABLE IF EXISTS `mind_core_text`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_core_text` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `LangId` int(11) NOT NULL,
  `Token` varchar(100) DEFAULT NULL,
  `Text` mediumtext,
  PRIMARY KEY (`EntityId`,`MemberId`,`LangId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_core_text`
--

LOCK TABLES `mind_core_text` WRITE;
/*!40000 ALTER TABLE `mind_core_text` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_core_text` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_util_binary`
--

DROP TABLE IF EXISTS `mind_util_binary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_util_binary` (
  `EntityId` int(11) NOT NULL,
  `BinaryMedium` mediumblob,
  `BinaryLong` longblob,
  PRIMARY KEY (`EntityId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_util_binary`
--

LOCK TABLES `mind_util_binary` WRITE;
/*!40000 ALTER TABLE `mind_util_binary` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_util_binary` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_util_data`
--

DROP TABLE IF EXISTS `mind_util_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_util_data` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `Key` int(10) unsigned zerofill NOT NULL,
  `ValInteger` int(11) DEFAULT NULL,
  `ValReal` double DEFAULT NULL,
  `ValRef` int(11) DEFAULT NULL,
  PRIMARY KEY (`EntityId`,`MemberId`,`Key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_util_data`
--

LOCK TABLES `mind_util_data` WRITE;
/*!40000 ALTER TABLE `mind_util_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_util_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_util_entity`
--

DROP TABLE IF EXISTS `mind_util_entity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_util_entity` (
  `StoreId` int(11) NOT NULL AUTO_INCREMENT COMMENT 'External ID, known by other components. Represents the current state of the entity',
  `PrimaryType` int(11) NOT NULL,
  `InitialId` int(11) NOT NULL,
  `CommitId` int(11) DEFAULT NULL COMMENT 'If the entity is versioned',
  `State` int(11) DEFAULT NULL COMMENT 'Null means "OK"',
  `Idx01` int(11) DEFAULT NULL,
  `Idx02` int(11) DEFAULT NULL,
  `Idx03` int(11) DEFAULT NULL,
  PRIMARY KEY (`StoreId`),
  UNIQUE KEY `StoreID_UNIQUE` (`StoreId`) /*!80000 INVISIBLE */,
  KEY `PRIMARY_TYPE` (`PrimaryType`) /*!80000 INVISIBLE */,
  KEY `INITIAL_ID` (`InitialId`,`CommitId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_util_entity`
--

LOCK TABLES `mind_util_entity` WRITE;
/*!40000 ALTER TABLE `mind_util_entity` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_util_entity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mind_util_text`
--

DROP TABLE IF EXISTS `mind_util_text`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mind_util_text` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `LangId` int(11) NOT NULL,
  `Token` varchar(100) DEFAULT NULL,
  `Text` mediumtext,
  PRIMARY KEY (`EntityId`,`MemberId`,`LangId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mind_util_text`
--

LOCK TABLES `mind_util_text` WRITE;
/*!40000 ALTER TABLE `mind_util_text` DISABLE KEYS */;
/*!40000 ALTER TABLE `mind_util_text` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test01_binary`
--

DROP TABLE IF EXISTS `test01_binary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `test01_binary` (
  `EntityId` int(11) NOT NULL,
  `BinaryMedium` mediumblob,
  `BinaryLong` longblob,
  PRIMARY KEY (`EntityId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test01_binary`
--

LOCK TABLES `test01_binary` WRITE;
/*!40000 ALTER TABLE `test01_binary` DISABLE KEYS */;
/*!40000 ALTER TABLE `test01_binary` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test01_data`
--

DROP TABLE IF EXISTS `test01_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `test01_data` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `Key` int(10) unsigned zerofill NOT NULL,
  `ValInteger` int(11) DEFAULT NULL,
  `ValReal` double DEFAULT NULL,
  `ValRef` int(11) DEFAULT NULL,
  PRIMARY KEY (`EntityId`,`MemberId`,`Key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test01_data`
--

LOCK TABLES `test01_data` WRITE;
/*!40000 ALTER TABLE `test01_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `test01_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test01_entity`
--

DROP TABLE IF EXISTS `test01_entity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `test01_entity` (
  `StoreId` int(11) NOT NULL AUTO_INCREMENT COMMENT 'External ID, known by other components. Represents the current state of the entity',
  `PrimaryType` int(11) NOT NULL,
  `InitialId` int(11) NOT NULL,
  `CommitId` int(11) DEFAULT NULL COMMENT 'If the entity is versioned',
  `State` int(11) DEFAULT NULL COMMENT 'Null means "OK"',
  `Idx01` int(11) DEFAULT NULL,
  `Idx02` int(11) DEFAULT NULL,
  `Idx03` int(11) DEFAULT NULL,
  PRIMARY KEY (`StoreId`),
  UNIQUE KEY `StoreID_UNIQUE` (`StoreId`) /*!80000 INVISIBLE */,
  KEY `PRIMARY_TYPE` (`PrimaryType`) /*!80000 INVISIBLE */,
  KEY `INITIAL_ID` (`InitialId`,`CommitId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test01_entity`
--

LOCK TABLES `test01_entity` WRITE;
/*!40000 ALTER TABLE `test01_entity` DISABLE KEYS */;
/*!40000 ALTER TABLE `test01_entity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test01_text`
--

DROP TABLE IF EXISTS `test01_text`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `test01_text` (
  `EntityId` int(11) NOT NULL,
  `MemberId` int(11) NOT NULL,
  `LangId` int(11) NOT NULL,
  `Token` varchar(100) DEFAULT NULL,
  `Text` mediumtext,
  PRIMARY KEY (`EntityId`,`MemberId`,`LangId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test01_text`
--

LOCK TABLES `test01_text` WRITE;
/*!40000 ALTER TABLE `test01_text` DISABLE KEYS */;
/*!40000 ALTER TABLE `test01_text` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-04  8:47:03
