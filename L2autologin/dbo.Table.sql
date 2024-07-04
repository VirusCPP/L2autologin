CREATE TABLE [dbo].[Accounts]
(
	[Id] INT NOT NULL PRIMARY KEY, 
    [Name] NCHAR(10) NOT NULL, 
    [Login] NCHAR(50) NOT NULL, 
    [Password] NCHAR(50) NOT NULL
)