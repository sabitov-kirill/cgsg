CREATE TABLE users(
    Id         INT                           NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Login      VARCHAR(16)                   NOT NULL,
    Password   VARCHAR(256),
    Role       ENUM('Admin, Client, Vendor') NOT NULL,
    Screnshots JSON                          DEFAULT '["ok.png"]',
    TasksCode  JSON,
);