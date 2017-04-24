/*
 * db.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: tao
 */
#include "db.h"

Db::Db(){

}

Db::~Db(){

}

bool Db::dataset_into_mysql(std::vector<std::vector<std::string>> &v){
	//MYSQL_RES *result;
	//MYSQL_ROW row;
	MYSQL *connection, mysql;
	int state;

	/* connect to the mySQL database at local-host */
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,"","root","root123", "",0, "/var/run/mysqld/mysqld.sock", 0);
	/* check for a connection error */
	if( connection == NULL ) {
		/* print the error message */
	    std::cout <<mysql_error(&mysql) << std::endl;
	    return false;
	}

	/* delete existing database */
	if ((mysql_select_db(connection, "test_db")) == 0){
	    	state = mysql_query(connection,
	    	                        "DROP SCHEMA test_db");
	    	if( state != 0 ) {
	    	        std::cout << "DB dropping failed" << std::endl;
	    	        return false;
	    	}
	}

	/* creatd database "test_db" */
	state = mysql_query(connection,
	                        "CREATE SCHEMA test_db");
	if( state != 0 ) {
	        std::cout << "DB creation failed" << std::endl;
	        return false;
	}

	/* select database */

	if ((state = mysql_select_db(connection, "test_db")) != 0){
	    	std::cout << "DB selection failed" << std::endl;
	    	return false;
	}

	/* create table */
	if ((state = mysql_query(connection,
		"CREATE TABLE test_table (name VARCHAR(10), score FLOAT, conf FLOAT , PRIMARY KEY (name))")) != 0){
	    std::cout << "Table creation failed" << std::endl;
	    return false;
	}

	/* insert rows */
	for (unsigned int i = 0; i < v.size(); i++){
		std::string str,token;
	    std::stringstream ss;

	    ss << "INSERT INTO test_table (name,score,conf) VALUES('" << v[i][0] << "', " <<
	    		v[i][1] << ", " << v[i][2] << ");";
	    	while (ss >> token){
	    		str += token;
	    		str += " ";
	    	}

	    	//std::cout << str.c_str() << std::endl;

	    	if ((state = mysql_query(connection, str.c_str())) != 0){
	    		std::cout << "Table insertion failed: " << i <<std::endl;
	    	    return false;
	    	}
	    }
	/* close the connection */
	mysql_close(connection);

	return true;
}

bool Db::get_score_ranked_data(std::vector<std::vector<std::string>> &v){
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;
	int state;

	/* connect to the mySQL database at local-host */
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,"","root","root123", "",0, "/var/run/mysqld/mysqld.sock", 0);
	/* check for a connection error */
	if( connection == NULL ) {
			/* print the error message */
		    std::cout <<mysql_error(&mysql) << std::endl;
		    return false;
	}

	if ((mysql_select_db(connection, "test_db")) != 0){
		std::cout << "Target DB does not exist. " << std::endl;
		return false;
	}

	/* make a query */
	if ((state = mysql_query(connection, "SELECT * FROM test_table ORDER BY score DESC;")) != 0){
	        std::cout << "Query failed" << std::endl;
	        return false;
	}

	/* must call mysql_store_result() before we can issue any
	 * other query calls */
	result = mysql_store_result(connection);
	ranked_dataset.clear();
	/* process each row in the result set */
	while( ( row = mysql_fetch_row(result)) != NULL ) {
		std::vector<std::string> v_temp;
		v_temp.push_back(row[0]);
		v_temp.push_back(row[1]);
		v_temp.push_back(row[2]);
		ranked_dataset.push_back(v_temp);
		v_temp.clear();
	}

	/* free the result set */
	mysql_free_result(result);
	/* close the connection */
	mysql_close(connection);
	return true;
}

bool Db::save_into_file(std::vector<std::vector<std::string>> v, const char* filename){
	std::ofstream fout;

	fout.open(filename);
	if (!fout)	return false;
	if (ranked_dataset.size() != 0) {
		for (unsigned int i = 0; i < ranked_dataset.size(); i++){
			for (unsigned int j = 0; j < ranked_dataset[i].size(); j++){
				fout << ranked_dataset[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();
	return true;
}

