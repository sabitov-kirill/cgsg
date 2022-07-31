/**
 *
 * CREATION DATE: 17.08.2021
 *
 * PROGRAMMER:    Kirill Sabitov.
 *
 * PURPOSE:       Audio books web store application.
 *                Server handle module.
 *
 */

 require('dotenv').config();
const express = require('express');
const Router = require('express').Router;
const bodyParser = require('body-parser');
const path = require('path');

const TaskController = require('./controllers/tasks-controller');

const octetStreamParser = bodyParser.raw({
    inflate: true,
    type: "application/octet-stream",
    limit: "200mb",
});

// Server model handle
class Server {
    applyMiddlewares() {
        this.app.use(bodyParser.json());
        this.app.use(bodyParser.urlencoded({ extended: true }));
    }

    setUpRouter() {
        // Creting router
        this.router = new Router();

        this.router.post('/task/submit', this.taskController.submit.bind(this.taskController));
        this.router.get('/task/request', this.taskController.request.bind(this.taskController));
        this.router.get('/task/tasks-pics', this.taskController.getTasksPics.bind(this.taskController));
        this.router.post('/task/remove-tasks-pic', this.taskController.removeTasksPic.bind(this.taskController));
        this.router.post('/task/screenshot', octetStreamParser, this.taskController.screenshot.bind(this.taskController));
    }

    handleBaseRequests() {
        // Setting up router to handle api requests
        this.app.use('/api', this.router);

        // Setting up react requests
        this.app.use(express.static(path.resolve(__dirname, './client/')));
        this.app.get('*', (request, result) => {
            result.sendFile(path.resolve(__dirname, './client/', 'index.html'));
        });
    }

    constructor(env) {
        // Creating http server
        this.app = express();
        this.server = require('http').createServer(this.app);
        this.taskController = new TaskController();

        // Setting up enviroment data
        this.port = process.env.PORT || 80;

        // Calling server initialisation functions
        this.applyMiddlewares();
        this.setUpRouter();
        this.handleBaseRequests();
    }

    async start() {
        try {
            // Listening on defined port
            this.server.listen(this.port, () => {
                console.log(`Server is listening on "${this.port}".`);
            });
        } catch (e) {
            console.log(`Server start error. ${e}.`)
        }
    }
}

module.exports = (env, path) => new Server(env, path);