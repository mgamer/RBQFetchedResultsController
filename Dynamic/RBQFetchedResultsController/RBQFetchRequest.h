//
//  RBQFetchRequest.h
//  RBQFetchedResultsControllerTest
//
//  Created by Adam Fish on 1/2/15.
//  Copyright (c) 2015 Roobiq. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Realm/RLMCollection.h>

@class RBQFetchRequest, RLMRealm, RLMObject, RLMRealmConfiguration, RLMArray;

#pragma mark - RBQFetchRequest

/**
 *  This class is used by the RBQFetchedResultsController to represent the properties of the fetch. The RBQFetchRequest is specific to one RLMObject and uses an NSPredicate and array of RLMSortDescriptors to define the query.
 */
@interface RBQFetchRequest : NSObject

/**
 *  RLMObject class name for the fetch request
 *
 *  For Swift this will be in the form of BundleName.ClassName since this is the actual class name
 */
@property (nonatomic, readonly) NSString *entityName;

/**
 *  The Realm in which the entity for the fetch request is persisted.
 */
@property (nonatomic, readonly) RLMRealm *realm;

/**
 *  The configuration object used to create an instance of RLMRealm for the fetch request
 */
@property (nonatomic, readonly) RLMRealmConfiguration *realmConfiguration;

/**
 *  Predicate supported by Realm
 *
 *  http://realm.io/docs/cocoa/0.89.2/#querying-with-predicates
 */
@property (nonatomic, strong) NSPredicate *predicate;

/**
 *  Array of RLMSortDescriptors
 *
 *  http://realm.io/docs/cocoa/0.89.2/#ordering-results
 */
@property(nonatomic, strong) NSArray *sortDescriptors;


/**
 *  Constructor method to create a fetch request for a given entity name in a specific Realm.
 *
 *  @param entityName Class name for the RLMObject
 *  @param realm      RLMRealm in which the RLMObject is persisted (if passing in-memory Realm, make sure to keep a strong reference elsewhere since fetch request only stores the path)
 *  @param predicate  NSPredicate that represents the search query
 *
 *  @return A new instance of RBQFetchRequest
 */
+ (instancetype)fetchRequestWithEntityName:(NSString *)entityName
                                   inRealm:(RLMRealm *)realm
                                 predicate:(NSPredicate *)predicate;

/**
 *  Retrieve all the RLMObjects for this fetch request in its realm.
 *
 *  @return RLMResults or RLMArray for all the objects in the fetch request (not thread-safe).
 */
- (id<RLMCollection>)fetchObjects;

/**
 *  Should this object be in our fetch results?
 *
 *  Intended to be used by the RBQFetchedResultsController to evaluate incremental changes. For
 *  simple fetch requests this just evaluates the NSPredicate, but subclasses may have a more
 *  complicated implementaiton.
 *
 *  @param object Realm object of appropriate type
 *
 *  @return YES if performing fetch would include this object
 */
- (BOOL)evaluateObject:(RLMObject *)object;

/**
 *  Create RBQFetchRequest in RLMRealm instance with an entity name
 *
 *  @param entityName Class name for the RLMObject
 *  @param realm      RLMRealm in which the RLMObject is persisted
 *
 *  @return A new instance of RBQFetchRequest
 */
- (instancetype)initWithEntityName:(NSString *)entityName
                           inRealm:(RLMRealm *)realm;

@end

#pragma mark - RBQArrayFetchRequest

@interface RBQArrayFetchRequest : RBQFetchRequest

@property (nonatomic, readonly) NSString *arrayProperty;

@property (nonatomic, readonly) RLMObject *object;

/**
 *  Constructor method to create a fetch request from a given RLMArray.
 *
 *  @param object           The RLMObject that contains the RLMArray that the fetch request will represent
 *  @param arrayProperty    The property name of the RLMArray contained on the RLMObject that will represent the fetch request
 *
 *  @return A new instance of RBQFetchRequest
 */
+ (instancetype)arrayFetchRequestForObject:(RLMObject *)object
                         withArrayProperty:(NSString *)arrayProperty;

/**
 *  Retrieve all the RLMArray for this fetch request
 *
 *  @return RLMArray for all the objects in the fetch request (not thread-safe).
 */
- (RLMArray *)array;

@end