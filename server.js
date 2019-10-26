var express = require('express');
var graphqlHTTP = require('express-graphql');
var { buildSchema } = require('graphql');

// Construct a schema, using GraphQL schema language

var schema = buildSchema(`
  type User {
    id: String
    name: String
    age: String
    companyId: String
  }

  type Company {
    id:String
    name: String
    description:String
  }


  type Query {
    user(id: Int): User
    company(id:Int):Company
    
  }


`);

var db = {
  'users':{
       '23':{id: "23",name: "Kasun",age: "21",companyId:"1"},
       '22':{id: "22",name: "Ruwan",age: "22",companyId:"2"},
       '21':{id: "21",name: "Raveen",age: "20",companyId:"2"}
  },

   'companies':{
       '1':{id:"1", name:"Apple", description:"iPhone"},
       '2':{id:"2", name:"Google", description:"Google pixel"},
       '3':{id:"3", name:"Tesla Motors", description:"Tesla"} 
}
};
// The root provides a resolver function for each API endpoint

//var root = {
  //user: function ({id}) {
    //return fakeDatabase[id];
  //}
//};

var root = {
  user: function ({id}){
    return db.users[id];
  },

  company: function({id}){
    return db.companies[id];

  }
};



var app = express();
app.use('/graphql', graphqlHTTP({
  schema: schema,
  rootValue: root,
  graphiql: true,
}));
app.listen(4000);
console.log('Running a GraphQL API server at localhost:4000/graphql');
