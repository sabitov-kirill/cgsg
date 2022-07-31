const fs = require('fs');
const path = require('path');

// Book controller class
class TaskController {
  constructor() {
    this.submitedTasks = [];
  }

  async submit(request, result) {
    try {
      const { taskNumber, taskCode } = request.body;
      this.submitedTasks[taskNumber - 1] = taskCode;

      result.status(200).redirect('/');
    } catch (error) {
      result.status(400).json({ error: error.message });
    }
  }

  async request(request, result) {
    try {
      result.status(200).json({ submitedTasks: this.submitedTasks });
    } catch (error) {
      result.status(400).json({ error: error.message });
    }
  }

  async screenshot(request, result) {
    try {
      const today = new Date();
      const fileName =
        '../client/screenshots/' +
        today.getFullYear() + '-' +
        (today.getMonth() + 1) + '-' +
        today.getDate() + '-' +
        today.getHours() + "-" +
        today.getMinutes() + "-" +
        today.getSeconds() + '.png';
      fs.writeFileSync(path.join(__dirname, fileName), request.body, (err) => {
        if (err) {
          return console.log(err);
        }
      });

      result.sendStatus(200);
    } catch (error) {
      result.status(400).json({ error: error.message });
    }
  }

  async getTasksPics(request, result) {
    try {
      const filesList = fs.readdirSync(path.join(__dirname, '../client/screenshots/'), (err) => {
        if (err) throw err;
      });

      result.status(200).json(filesList);
    } catch (error) {
      result.status(400).json({ error: error.message });
    }
  }

  async removeTasksPic(request, result) {
    try {
      const { tasksPicFileName } = request.body;

      fs.unlinkSync(
        path.join(__dirname, '../client/screenshots/' + tasksPicFileName), 
        (err) => { if (err) return; }
      );

      result.sendStatus(200);
    } catch (error) {
      result.status(400).json({ error: error.message });
    }
  }
}

module.exports = TaskController; 