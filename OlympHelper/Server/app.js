/**
 *
 * CREATION DATE: 17.08.2021
 *
 * PROGRAMMER:    Kirill Sabitov.
 *
 * PURPOSE:       Audio books web store application.
 *                Server entry point.
 *
 */

// Creating new server exemplar and running it
const server = require('./server')(process.env);
server.start();