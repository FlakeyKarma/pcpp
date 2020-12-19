# pcpp
A C++ library for Postgres creation, modification, queries, and deleting.

## Intro
This is a library that is supposed to help with writing C++ code to interact with Postgres databases.

This will start as a bare-bones library, as that's all I need at the moment. However, as I progress through my database journey I will continue to update the capabilities of this library.

Just one more thing: Since modularity can be the difference between further pieces being developed in the future, one of my main goals is modularity of this puzzle so it can be put together in different ways for dynamic use. If this claim falls short in any areas, feel free to shoot a message my way!

>### Create

>### Alter

>### Query
>`getQuery`
>>Get query from user, directly.
>`setQuery`
>>Set query by the user specified in object.
>`setTable`
>>Set tables to use.
>`setWhere`
>>Enter explicit WHERE statement.
>`WHERE`
>>Buid where clause.
>`where_combination`
>>Combine where-statements given.
>`findTable`
>>Find and return char array of the table name given that contains specified column.
>`bldQuery`
>>Combine all aspects of query to a final statement with the contents of the QRY struct.
>`runQuery`
>>Finally run the query built within object's QRY struct.

>### Destroy
